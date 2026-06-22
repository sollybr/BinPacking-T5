import os
import re
import subprocess
from pathlib import Path

SAMPLES_DIR = Path("samples")
LOG_DIR = Path("logs")
BINARY = "./build/binpacking"

PARTIDAS = 3
TEMPO = 2
VIZ = 10


cost_re = re.compile(r"(\d+)\s*bins")  # matches "final_bins=XX" or similar


def extract_costs(text):
    values = []

    for line in text.splitlines():
        # adapt to your output format
        if "bins=" in line:
            m = re.search(r"bins=(\d+)", line)
            if m:
                values.append(int(m.group(1)))

        elif "final_bins=" in line:
            m = re.search(r"final_bins=(\d+)", line)
            if m:
                values.append(int(m.group(1)))

        elif "Melhor solucao" in line:
            m = re.search(r"(\d+)", line)
            if m:
                values.append(int(m.group(1)))

    return values


def run_instance(file_path: Path):
    print(f"[RUN] {file_path.name}")

    cmd = [
        BINARY,
        str(file_path),
        "--partidas", str(PARTIDAS),
        "--tempo", str(TEMPO),
        "--vizinhanca", str(VIZ),
    ]

    result = subprocess.run(cmd, capture_output=True, text=True)
    output = result.stdout + "\n" + result.stderr

    costs = extract_costs(output)

    if not costs:
        return None, output

    return {
        "min": min(costs),
        "max": max(costs),
        "avg": sum(costs) / len(costs),
        "runs": len(costs),
    }, output


def main():
    LOG_DIR.mkdir(exist_ok=True)

    summary_path = LOG_DIR / "summary.log"

    with open(summary_path, "a") as summary:

        summary.write("\n=== NEW BATCH ===\n")

        for sample in sorted(SAMPLES_DIR.iterdir()):
            if not sample.is_file():
                continue

            subprocess.run(["bash", "build.sh"], check=True)

            stats, output = run_instance(sample)

            log_file = LOG_DIR / f"{sample.stem}.log"
            log_file.write_text(output)

            if stats is None:
                summary.write(f"{sample.name} -> NO DATA\n")
                continue

            line = (
                f"{sample.name} | "
                f"min={stats['min']} "
                f"avg={stats['avg']:.2f} "
                f"max={stats['max']} "
                f"runs={stats['runs']}\n"
            )

            print(line.strip())
            summary.write(line)


if __name__ == "__main__":
    main()

import pandas as pd
import matplotlib.pyplot as plt

latency = pd.read_csv("benchmarks/latency_results.csv")
throughput = pd.read_csv("benchmarks/throughput_results.csv")

# Separate latency chart
latency.plot(x="Implementation", y="AvgLatency(us)", kind="bar", legend=False)
plt.ylabel("Latency (µs)")
plt.title("OrderBook Latency Comparison")
plt.tight_layout()
plt.savefig("benchmarks/plots/latency_histogram.png")

# Separate throughput chart
throughput.plot(x="Implementation", y="Throughput(ops/sec)", kind="bar", legend=False)
plt.ylabel("Throughput (ops/sec)")
plt.title("OrderBook Throughput Comparison")
plt.tight_layout()
plt.savefig("benchmarks/plots/throughput_chart.png")

# Dual-axis combined chart
df = pd.merge(latency, throughput, on="Implementation")
fig, ax1 = plt.subplots()
ax1.set_xlabel("Implementation")
ax1.set_ylabel("Latency (µs)", color="blue")
ax1.bar(df["Implementation"], df["AvgLatency(us)"], color="blue", alpha=0.6)
ax1.tick_params(axis="y", labelcolor="blue")

ax2 = ax1.twinx()
ax2.set_ylabel("Throughput (ops/sec)", color="red")
ax2.plot(df["Implementation"], df["Throughput(ops/sec)"], color="red", marker="o")
ax2.tick_params(axis="y", labelcolor="red")

plt.title("OrderBook Benchmark Results")
plt.tight_layout()
plt.savefig("benchmarks/plots/combined_dual_axis.png")
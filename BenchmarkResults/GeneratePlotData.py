import json
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure

defaultInstructionSetBenchmarkFile = open("DefaultInstructionSet.json")
defaultInstructionSetBenchmarkDataFrame = json.load(defaultInstructionSetBenchmarkFile)

SSEInstructionSetBenchmarkFile = open("SSE.json")
SSEInstructionSetBenchmarkDataFrame = json.load(SSEInstructionSetBenchmarkFile)

AVXInstructionSetBenchmarkFile = open("AVX.json")
AVXInstructionSetBenchmarkDataFrame = json.load(AVXInstructionSetBenchmarkFile)

plotData = { 
    "Default" : defaultInstructionSetBenchmarkDataFrame["benchmarks"][0]["items_per_second"],
    "SSE" : SSEInstructionSetBenchmarkDataFrame["benchmarks"][0]["items_per_second"],
    "AVX" : AVXInstructionSetBenchmarkDataFrame["benchmarks"][0]["items_per_second"],
    }

instructionSets = list(plotData.keys())
benchmarkTimes = list(plotData.values())

figure(num = None, figsize = (16, 9), dpi = 80, facecolor = 'w', edgecolor = 'k')
plt.bar(instructionSets, benchmarkTimes, width = 0.2, color = "maroon")
plt.xlabel("Instruction set")
plt.ylabel("multiplications/sec")
plt.title("Matrix 4x4 multiplication")
plt.savefig("Matrix 4x4 multiplication comparison.png")
plt.show()
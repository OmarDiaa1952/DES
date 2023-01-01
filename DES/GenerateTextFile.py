import random
import time
from tqdm import tqdm

hexa = ["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"]

numOfChar = int((float(input("Please input size of generated hexa text file in GB: ")) * 1000000000))
#print(numOfChar)

start = time.process_time()
with open("input.txt", 'w') as file:
    # i is counter for num of characters start from zero to end
    for i in tqdm(range(0, numOfChar)):
        val = random.randint(0, 15)
        file.write(hexa[val])

print("The File is ready")   
print("Time taken is: " + time.process_time() - start)
# -*- coding: utf-8 -*-
"""
Created on Sat Sep  5 12:22:43 2020

@author: Owner
"""
f = open ("Puzzle_1.txt", "r")
arr = []
characters = []
for line in f:
    eff = int(line.index('"', 31))
    eff2 = int(line.index('"', eff+1))
    arr.append(int(line[eff+1: eff2]))
#    print(line[eff2+2: eff2+3])
    characters.append(line[eff2+2: eff2+3])
  
  
n = len(arr)
for i in range(n-1): 
    # range(n) also work but outer loop will repeat one time more than needed. 
  
        # Last i elements are already in place 
        for j in range(0, n-i-1): 
  
            # traverse the array from 0 to n-i-1 
            # Swap if the element found is greater 
            # than the next element 
            if arr[j] > arr[j+1] : 
                arr[j], arr[j+1] = arr[j+1], arr[j] 
                characters[j], characters[j+1] = characters[j+1], characters[j]
print("sorted list is")
blurp = ""
for i in characters:
    blurp = blurp + i
print (blurp)
sorty = ""
for i in arr:
    sorty = sorty + string(i) + ", "
print("Sorted array?")
print(sorty)
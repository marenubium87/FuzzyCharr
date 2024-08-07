#faster solution?

nums = [-10, -4, -3, -2, -1]
target = -7

def twoSum(nums, target):
    nums_copy = nums.copy()
    nums_copy.sort()
    #will stop at 1th element since there always needs to be at least
    #one element before this to attempt a sum
    i = 0
    for j in range(len(nums_copy) - 1, 0, -1):
        #if j is "too big" then this inner loop will not run and
        #j will decrement again without incrementing i
        while nums_copy[i] < target - nums_copy[j]:
            i = i + 1
        if nums_copy[i] == target - nums_copy[j]:
            break
    
    #search back through original list for indices of correct values
    k = 0
    l = 0
    flag = False
    for x in range(len(nums)):
        if nums[x] == nums_copy[i] and flag == False:
            k = x
            flag = True
        elif nums[x] == nums_copy[j]:
            l = x
    return [k, l]

print(twoSum(nums, target))
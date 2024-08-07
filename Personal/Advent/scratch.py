nums = [1, 2, 3]

results = []
current = []
def include(current, i):
    included = current + [nums[i]]
    unincluded = current.copy()
    if i < len(nums) - 1:
        include(included, nums[i + 1])
        include(unincluded, nums[i + 1])
    else:
        results.append(included)
        results.append(unincluded)

include(current, 0)
print(results)

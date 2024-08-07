#slow solution
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        for i in range(len(nums)):
            for j in range(len(nums)):
                if j != i and target - nums[j] == nums[i]:
                    return [i, j]


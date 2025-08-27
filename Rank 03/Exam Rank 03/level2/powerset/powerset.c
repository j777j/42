#include <stdio.h>
#include <stdlib.h>

// Helper function to print a valid subset
void	print_subset(int *subset, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%d", subset[i]);
		if (i < size - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

// Simple bubble sort to sort the initial array
void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// The core recursive function to find combinations
// target: the remaining sum we need to find
// nums: the sorted array of numbers
// size: total size of the nums array
// start_index: the index from which we are allowed to start picking numbers
// subset: the temporary array holding the current combination
// subset_size: the current number of elements in the subset
void	find_combinations(int target, int *nums, int size, int start_index,
		int *subset, int subset_size)
{
	int	i;

	// Base case: we found a combination that sums up to the original target
	if (target == 0)
	{
		print_subset(subset, subset_size);
		return ;
	}
	// Pruning: if target becomes negative, this path is invalid
	if (target < 0)
	{
		return ;
	}
	// Main recursive loop
	i = start_index;
	while (i < size)
	{
		// 1. Include the number nums[i]
		subset[subset_size] = nums[i];
		// 2. Recurse: find the rest of the sum (target - nums[i])
		//    Crucially, the next search starts from 'i + 1',
		never looking back.find_combinations(target - nums[i], nums, size, i
			+ 1, subset, subset_size + 1);
		// 3. Backtrack: The recursive call is over, so we conceptually
		//    remove nums[i] by letting the loop continue to the next number.
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	target;
	int	size;
	int	*nums;
	int	*subset;
	int	i;

	if (argc < 2)
		return (1);
	target = atoi(argv[1]);
	size = argc - 2;
	if (size < 0)
		size = 0;
	// Allocate memory
	nums = (int *)malloc(sizeof(int) * size);
	subset = (int *)malloc(sizeof(int) * size);
	if (!nums || !subset)
	{
		free(nums);
		free(subset);
		return (1);
	}
	// Parse numbers from arguments
	i = 0;
	while (i < size)
	{
		nums[i] = atoi(argv[i + 2]);
		i++;
	}
	// The key step: sort the array first!
	sort_array(nums, size);
	// Start the search for combinations
	find_combinations(target, nums, size, 0, subset, 0);
	// Clean up
	free(nums);
	free(subset);
	return (0);
}

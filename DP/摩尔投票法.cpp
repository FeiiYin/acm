/// https://www.jianshu.com/p/c19bb428f57a
/// p判断数组中是否有元素大于一半，或者其他类似的
/// 时间复杂度 O(n)，空间复杂度 O(1)
/**
 * 算法基础：摩尔投票法
 * @param nums
 * @return
 */
public int majorityElement(int[] nums) {

    int majority = -1;

    int count = 0;

    for (int num : nums) {
        if (count == 0) {
            majority = num;
            count++;
        } else {
            if (majority == num) {
                count++;
            } else {
                count--;
            }
        }
    }

    int counter = 0;
    if (count <= 0) {
        return -1;
    } else {
        for (int num : nums) {
            if (num == majority) counter ++;
        }
    }

    if (counter > nums.length / 2) {
        return majority;
    }

    return -1;
}

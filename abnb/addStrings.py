class Solution(object):
    def addStrings(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        l1 = list(num1)
        l2 = list(num2)

s1 = Solution()
n1 = ["1", "0", "11"]
n2 = ["0", "1", "234"]
for i1,i2 in zip(n1, n2):
    print(i1 + " + " + i2 + " = " + s1.addStrings(i1, i2))

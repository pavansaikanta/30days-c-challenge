ALGORITHM: 
1. Start.
2. Read the number of readings N. If N is less than 5 or greater than 12, display an error message and ask again.
3. Read N integer values into a one-dimensional array. If any reading is less than 0 or greater than 1000, display an error message and ask for that reading again.
4. Display all the original readings.
5. Initialize sum to 0 and set max and min to the first array element.
6. Traverse the array to calculate the sum, maximum, and minimum.
7. Calculate the average by dividing sum by N.
8. Find the second-largest distinct value by checking for the largest value smaller than max. If no such value exists, display a message.
9. Count the local peaks. An element is a local peak if it is strictly greater than both its immediate neighbours. Do not consider the first and last elements.
10. Find the longest strictly increasing contiguous run by comparing each element with the previous element.
11. Read the rotation amount K and normalize it using the formula ((K % N) + N) % N to handle negative and large rotations.
12. Rotate the array to the right using the normalized rotation amount, a temporary variable, and loops. Do not use another array.
13. Read the last two digits R of the registration number and calculate the divisor D using the formula D = (R % 9) + 1.
14. Count the elements in the rotated array that are divisible by D.
15. Display the divisor and the number of divisible values.
16. Stop.



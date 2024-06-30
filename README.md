# Orderbook
Testing task for company

How to run this project? You should download all files and run Website Analytics.sin by using Visual Studio. If you haven`t Visual Studio, copy and paste code from main.cpp in your IDE.

Efficiency of the Solution

Adding an Order:
Insertion: When a new order is added, it is inserted into either the buy or sell list.
Sorting: After insertion, the respective list (buy or sell) is sorted.
Time Complexity: The insertion operation is 𝑂(1), but the sorting operation is 𝑂(𝑛 log⁡ 𝑛) where 𝑛 is the number of orders in the list. Thus, the complexity of adding an order is 
𝑂(𝑛 log 𝑛).

Matching Orders:
While Loop: The matching process involves a while loop that continues as long as there are orders to be matched and the top sell price is less than or equal to the top buy price.
Operations Inside Loop: Within the loop, the orders are matched, and the amounts are updated. The most expensive operation inside the loop is the removal of an order from the front of the list, which is 𝑂(𝑛) if using a simple vector.
Time Complexity: If we assume each match involves one removal operation and potentially one insertion back into the list, the complexity of each match operation can be considered 𝑂(𝑛). In the worst case, if all orders need to be processed, this would lead to a time complexity of 𝑂(𝑛^2).

Big O Classification
Adding an Order: 𝑂(𝑛 log 𝑛)
Matching Orders: 𝑂(𝑛^2) in the worst-case scenario

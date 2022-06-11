# Expense Tracker
>Run the ***batch file()*** to excute the program.
## **Instruction** 
First of all, you need an account with the expense tracker system. If you don't have an account, you need to create it. After you have the account, you can login and start using the function we provided in the system.  
***
After you login, you will see the main operation menu below.
```
[0] Adding consumption record
[1] Remove consumption record.
[2] Search certain record according to date.
[3] Search certain record according to category.
[4] Consumption analysis.
[5] Exit.
[6] Log out.
```
You can choose what you want to do by entering the **coordinating number**.
### **Operation Discription**
- *Adding consumption record*  
    - Input the date, category, and cost of the consumption     record you want to add.
- *Remove consumption record*
    - First, input the month of the consumption you want to delete. Then, the system will list all the consumption in the month you chose.  
    - Input the date, category, and cost of the consumption record you want to delete.  
- *Search certain record according to date*
    - First, input the month you want to check. Then enter the beginning day and ending day of the interval you want.  
    - The system will list all the consumption in the interval you chose and order the list in date.
- *Search certain record according to category.*
    - First, input the month you want to check. Then enter the category you want.  
    - The system will list all the consumption in the category you chose and order the list in date.
- *Consumption analysis.*
    - First, input the month you want to analyze.  
    - Then, the system will ask you whether to consider the budget or not. If you don’t consider the budget, you won’t get the suggestions of the budget for next month.  
    - Next, the system will list the month summary, including the sum of expenses in each category, total revenue, total expense, and balance.  
    - After that, you can choose to get the analysis of expenses and the suggestion of the budget for next month (if you had chosen to consider the budget).
- *Exit*
    - To terminate the program.
- *Log out*
    - To log out the account you are using now. You can use other accounts to login the system after you choose this option.
***
After the program is terminated, user can actually access the data in the backend in the program directory. (which is store in .**csv** format.)

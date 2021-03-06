# BundySystem
A system that can be used in a factory like setting to allow employees to clock in and out for shift work. Created using C++ (UNIX)


Bundy System

This system is designed to be used for shift work in places such as factories where people clock in and out to start and end their day. 

Each week the program saves payslips for each employee showing their weekly pay, tax, and superannuation. It also shows the yearly amount accumulated to that week as well.

A summary of the yearly work is also saved for the employer so they can see which people worked certain days.

Employers/Employees are also able to use the program to see the days of the year that they have worked and how many hours they worked in that shift.

If someone forgets to clock out at the end of the day there is a tool to help the employer go through and manually check and add the correct amount of hours worked by the employee, in case that the employee tried to leave early and cover it up by no clocking out.

Initialisation

Initially, the program will create a data folder to store each year’s work information. A folder will then be created for the current financial year which stores payslips for employees for each week and a summary for the employer. When a new financial year begins, a folder is created for the new financial year. The admin password will initially be set to “admin” which can be changed with the “change password” command.

Commands used to control the program

add employee - Allows the user to add a new employee to the current list of workers. Only available to the employer.

remove employee - Causes the specified employee to be set to not currently work. This will cause their name to be removed from the employee list at the end of the financial year but retain their working history. Only available to the employer.

re-employ employee - Causes the specified employee to be set to be currently working again. Only available to the employer.

list employees - Lists the names of the employees who are stored in the bundySystem.

change wage - Allows the employer to modify a workers wage. Only available to the employer.

clock in - Allows an employee to set the start of their shift.

clock out - Ends the employee’s current shift. Also informs them of how long they worked that day.

review working history - Prints the days of the year the employee has worked on as well as the hours that they worked for these days.

resolve conflicts- Allows the employer to go through the working history and modify the hours an employee has worked if they forgot to clock out at the end of their shift. Only available to the employer.

change banking details - Allows the employer to change an employee’s banking details if they decide that they want their payment to be placed into a different account. Only available to the employer.

review employee data - Allows the employer to review employee information such as wage, tax file number, banking details and if they are currently employed. Only available to the employer due to showing banking details.

change password - Gives the employer a way to change their password from the originally set password. Only available to the employer. The initial password is “admin”.

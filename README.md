#    USER TASK MANAGER
#### Description:
     The prototype is a  command-line application designed for task management. It allows users to add new tasks, delete tasks, and list all existing tasks.
     The goal was to create an intuitive interface where users could interact with their to-do lists and follow up on tasks by adding descriptions.
     Delete completed or unrelated items. View a complete list of functions at any time. Also, Store The Timaing Of the User
     When They Add the Task And The Last Date To be Completed, This application stores the Task in a Text file, which ensures the data is stored in memory.

     # Features
    1. Add a Task
       ->Description:
            The user can add new tasks by typing a description of the task.
            The user also has the option to input the specific time they plan to complete the task.
            This can be in the format of HH: MM or YYYY-MM-DD HH: MM for more detailed scheduling.

        ->Benefits:
            This feature allows users to manage their tasks with clear descriptions and time goals, helping them organize their workload efficiently.



        2. List Tasks
        ->Description:
                Users can view a list of all tasks they’ve added. The details of each task include:
                Task ID: A unique identifier for each task.
                Description: The text the user entered to describe the task.
                Added Time: The timestamp shows when the task was created.
                Scheduled Time: The user-provided time by which the task should be completed.
                Completion Status: Whether the task is marked as completed or not.
         ->Benefits:
                This feature provides users with a clear overview of all tasks they’ve created,
                along with key details for better task tracking and planning.



     3. Remove Task
           ->Description:
                  Users can remove tasks from the list. This could be useful when a task is completed or is no longer relevant.
                  The user simply needs to provide the ID of the task they wish to delete.
            ->Benefits:
                  This allows users to keep their task list clean and focused by removing unnecessary or completed tasks, preventing clutter.



     4. Mark a Task as Completed / Show Completed Tasks / Show Incomplete Tasks
            ->Mark Task as Completed:
                  The user can mark any task as completed by entering its ID. Once a task is completed, it can be distinguished from other tasks in the list.
            ->Show Completed Tasks:
                  The user can view a list of tasks that have been marked as completed. Each task will display the same details as the general list, but only for completed tasks.
            ->Show Incomplete Tasks:
                  Similarly, the user can list only those tasks that have not yet been marked as completed.
            ->Benefits:
                  These options provide flexibility for users to focus on either unfinished work or completed tasks. By distinguishing between the two, users can track progress more effectively

     #Summary of Benefits:
         -> This task management system is designed to be intuitive and efficient for handling daily tasks.
         -> It supports task addition, removal, and status tracking (completed/incomplete), and provides a clear display of task details for better organization.
         -> The system helps users stay on top of their tasks, prioritize what's important, and maintain an up-to-date task list.


     # Code Properties
     The code is implemented efficiently and demonstrates good practices for managing tasks dynamically.
     1 - Dynamic Memory Management
     2 - Persistent Storage
     3 - Clear Task Management



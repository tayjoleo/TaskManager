#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

    class Task
    {
    public:
        string description;
        string deadline;
        int priority;
        bool completed;

        // Constructor to initialize a task
        Task(string desc, string dl, int prio)
            : description(desc), deadline(dl), priority(prio), completed(false) {}

        // Mark task as completed
        void markCompleted()
        {
            completed = true;
        }

        // Display task information
        void display() const 
        {
        
            cout << "Task: \033[35m" << description << "\033[0m" << endl
                << "Deadline: " << deadline << endl
                << "Priority: " << priority << endl
                << "Completed: ";
                if (completed) 
                {
                    cout << "\033[32mYes\033[0m";  // Green for "Yes"
                }
                else {
                    cout << "\033[31mNo\033[0m";   // Red for "No"
                }
            cout << endl << endl;
            cout << "\033[0m";
        }
    };

    class ToDoList
    {
    public:
        void addTask()
        {
            string desc, dl;
            int prio;

            cout << "Enter a task description: ";
            cin.ignore();
            getline(cin, desc);

            cout << "Enter a task deadline (YYYY-MM-DD): ";
            cin >> dl;

            cout << "Enter a task priority (1 = High, 5 = Low): ";
            cin >> prio;

            tasks.push_back(Task(desc, dl, prio)); // Adds the task to the list
            cout << "Task added successfully!" << endl;
        }

        void viewTasks() const
        {
            if (tasks.empty())
            {
                cout << "Nothing to do right now." << endl;
                return;
            }

            for (size_t index = 0; index < tasks.size(); index++)
            {
                cout << index + 1 << ". ";
                tasks[index].display();
            }
        }

        void markTaskCompleted()
        {
            if (tasks.empty())
            {
                cout << "Everything is completed." << endl;
                return;
            }

            int taskNumber;
            cout << "Enter the task number to mark as completed: ";
            cin >> taskNumber;

            if (taskNumber > 0 && taskNumber <= tasks.size())
            {
                tasks[taskNumber - 1].markCompleted();
                cout << "Task " << taskNumber << " marked as completed!" << endl;
            }
            else
            {
                cout << "Invalid task number." << endl;
            }
        }

        void saveTasksToFile()
        {
            ofstream outFile("tasks.txt"); // Opens a file for writing

            for (const auto& task : tasks)
            {
                outFile << task.description << endl
                    << task.deadline << endl
                    << task.priority << endl
                    << task.completed << endl;
            }
            cout << "Tasks saved to tasks.txt" << endl;
            outFile.close();
        }

        void loadTasksFromFile()
        {
            ifstream inFile("tasks.txt");
            string desc, dl;
            int prio;
            bool comp;

            while (getline(inFile, desc) &&
                getline(inFile, dl) &&
                (inFile >> prio) &&
                (inFile >> comp))
            {
                inFile.ignore();

                Task loadedTask(desc, dl, prio);
                loadedTask.completed = comp;
                tasks.push_back(loadedTask);
            }
            cout << "Tasks loaded from tasks.txt" << endl;
            inFile.close();
        }

    
    private:
        vector<Task> tasks; // Vector to store tasks
    };
    
    int main()
    {
        ToDoList toDoList;
        int choice;

        do
        {
            cout << "\033[33m"; 
            cout << "\n--- To-Do List Menu ---\n";
            cout << "\033[0m";
            cout << "1. Add Task\n";
            cout << "2. View All Tasks\n";
            cout << "3. Mark Task as Completed\n";
            cout << "4. Save Tasks to File\n";  
            cout << "5. Load Tasks from File\n"; 
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            cout << endl;

            switch (choice) 
            {
            case 1:
                toDoList.addTask();
                break;
            case 2:
                toDoList.viewTasks();
                break;
            case 3:
                toDoList.markTaskCompleted();
                break;
            case 4:
                toDoList.saveTasksToFile();  
                break;
            case 5:
                toDoList.loadTasksFromFile();  
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option. Try again!" << endl;
            }
        } while (choice != 0);
        
        system("pause");
    }

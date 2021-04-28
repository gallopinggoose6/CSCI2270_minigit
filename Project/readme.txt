minigit - Tyler Renken's implementation

This program provides all of the functionality as specified in Phase 1 in the writeup

This is a basic version control program which works while it's running in a terminal window separate from the workspace.

As an addition, the program will save its state in a .REPO file inside of the .minigit directory. When the program is run, it can restore its state from the information contained in the .REPO file. This occurs automatically whenever the program is run in the directory containing the .minigit directory. If a .minigit directoy does not exist, the user has an option to create a new repo.

With it, you can initialize a repository, similar to git, which will create the .minigit directory.
You can then add files to be tracked, remove files from tracking, commit versions of those files so that you may check them out later.
To do this, you must type 'add', 'remove', 'commit', or 'checkout' in lowercase. Do not add anything after the command.
The program will then ask for the necessary information to complete the operation,
either asking for the relative path name of the file you want to add or remove, or which commit you want to checkout.
To exit the program, type 'exit', or 'quit'. To display a message with a list of commands, type 'help'

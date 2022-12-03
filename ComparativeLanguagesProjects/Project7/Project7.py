"""
Wyatt Rose
Project 7: Student Records
Reads from a provided text file and writes to the stdout and a new txt file
"""
import re
import sys
from os.path import exists


class Student():

    def __init__(self, uid, first, last, level):
        self.uid = uid
        self.first = first
        self.last = last
        self.level = level
        self.classes = []

    def addClass(self, course):
        self.classes.append(course)

    def __str__(self):
        string = f"UID: {self.uid}\nFirst Name: {self.first}\nLast Name: {self.last}\nLevel: {self.level}\nCLASSES:\n"
        for course in self.classes:
            string += f"{course}\n"
        return string

    def __iter__(self):
        self.current = 0
        return

    def __next__(self):
        if self.current < len(self.classes):
            returnVal = self.classes[self.current]
            self.current += 1
            return returnVal
        else:
            raise StopIteration


students = []

"""
loadFile: inputs data into student objects from studentRecordsIn.txt 
"""
def loadFile():

    # Check if studentRecordsIn.txt is not present
    if not exists("studentRecordsIn.txt"):
        sys.exit("Wordlist not found!")

    # open student records text file
    with open("studentRecordsIn.txt") as file:

        # each line in file is a record
        for line in file:
            line = line.strip()
            studInfo = re.split('\s', line)

            uid = studInfo[0]
            first = studInfo[1]
            last = studInfo[2]
            level = studInfo[3]

            del studInfo[0]
            del studInfo[0]
            del studInfo[0]
            del studInfo[0]

            localStud = Student(uid, first, last, level)
            students.append(localStud)

            for element in studInfo:

                students[len(students) - 1].addClass(element)


"""
printFile: prints student data to output file and console
"""
def printFile():

    print(f"Student Records\n===============\n\n")

    # if studentRecordsOut.txt doesnt exist, create it
    with open("studentRecordsOut.txt", 'w') as fileOut:
        fileOut.write(f"Student Records\n===============\n\n")

        for student in students:

            # write to file
            fileOut.write(str(student))
            fileOut.write(f"'''''''''\n'''''''''\n\n")

            # print to console
            print(str(student))
            print(f"'''''''''\n'''''''''\n\n")


loadFile()
printFile()

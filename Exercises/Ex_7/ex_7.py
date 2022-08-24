'''
Name: Artiom Berengard
Assignment: ex_7
'''

#from my_plot import plot

input_file = 'persons.txt'
#plot = plot('Input:', input_file)


# Defying the class of Person
class Person:
    def __init__(self, firstName="", lastName="", day=0, month=0, year=0, height=0, weight=0):
        self.firstName = firstName
        self.lastName = lastName
        self.day = day
        self.month = month
        self.year = year
        self.height = height
        self.weight = float(weight)

# Using a for loop in order to obtain a list of persons, ignoring the '\n'
persons = []
numOfPersons = 0
with open(input_file) as file:
    for line in file:
        line = line.strip()
        persons.append(Person(*line.split(',')))
        numOfPersons += 1

'''
Function Name: weightToNum
Input: The person we compare
Output: The persons weight, after casting
Function Operation: This is a helper function that does casting to the weight of person and returns it. 
'''
def weightToNum(person):
    weightNum = float(person.weight)
    return weightNum

'''
Function Name: dateToNum
Input: The person we compare
Output: The calculated person's date as a integer 
Function Operation: This helper function calculates the person's date as a integer and returns it. 
'''
def dateToNum(person):
    finalNum  = int(person.year) * 100
    finalNum += int(person.month)
    finalNum = int(finalNum) * 100
    finalNum += int(person.day)
    return finalNum

'''
Function Name: sortByBMI
Input: The person we compare
Output: The calculated person's BMI
Function Operation: This is a helper function that calculates the person's BMI by the formula and returns it. 
'''
def sortByBMI(person):
    cmInMeter = 100
    height = float(person.height)
    heightInCm = float(height/cmInMeter)
    weight = float(person.weight)
    BMI = float(weight/(heightInCm*heightInCm))
    return BMI

#Sorting the list of persons by the first name, using lambda. Later, creating a CSV file with the sorted list.
persons.sort(key=lambda x: x.firstName)
firstNameCSV = open("by_first_name.csv", "w")
for person in persons:
    firstNameCSV.write(
        f"{person.firstName},{person.lastName},{person.day},{person.month},{person.year},{person.height},{person.weight:.2f}"+"\n")
firstNameCSV.close()
#plot('By first name:', 'by_first_name.csv')

#Sorting the list of persons by the last name, using lambda. Later, creating a CSV file with the sorted list.
persons.sort(key=lambda x: x.lastName)
lastNameCSV = open("by_last_name.csv", "w")
for person in persons:
    lastNameCSV.write(
        f"{person.firstName},{person.lastName},{person.day},{person.month},{person.year},{person.height},{person.weight:.2f}"+"\n")
lastNameCSV.close()
#plot('By last name:', 'by_last_name.csv')

#Sorting the list of persons by the date, using lambda and the helper function as described above.
#Later, creating a CSV file with the sorted list.
persons.sort(key=lambda x: dateToNum(x))
dateCSV = open("by_date.csv", "w")
for person in persons:
    dateCSV.write(
        f"{person.firstName},{person.lastName},{person.day},{person.month},{person.year},{person.height},{person.weight:.2f}"+"\n")
dateCSV.close()
#plot('By date:', 'by_date.csv')

#Sorting the list of persons by the height, using lambda. Later, creating a CSV file with the sorted list.
persons.sort(key=lambda x: x.height)
heightCSV = open("by_height.csv", "w")
for person in persons:
    heightCSV.write(
        f"{person.firstName},{person.lastName},{person.day},{person.month},{person.year},{person.height},{person.weight:.2f}"+"\n")
heightCSV.close()
#plot('By height:', 'by_height.csv')

#Sorting the list of persons by the weight, using lambda and a helper function as described above.
#Later, creating a CSV file with the sorted list.
persons.sort(key=lambda x: weightToNum(x))
weightCSV = open("by_weight.csv", "w")
for person in persons:
    weightCSV.write(
        f"{person.firstName},{person.lastName},{person.day},{person.month},{person.year},{person.height},{person.weight:.2f}"+"\n")
weightCSV.close()
#plot('By weight:', 'by_weight.csv')

#Sorting the list of persons by the BMI, using lambda and a helper function as described above.
#Later, creating a CSV file with the sorted list.
persons.sort(key=lambda x: sortByBMI(x))
BMI_CSV = open("by_BMI.csv", "w")
for person in persons:
    BMI_CSV.write(
        f"{person.firstName},{person.lastName},{person.day},{person.month},{person.year},{person.height},{person.weight:.2f}"+"\n")
BMI_CSV.close()
#plot('By bmi:', 'by_BMI.csv')


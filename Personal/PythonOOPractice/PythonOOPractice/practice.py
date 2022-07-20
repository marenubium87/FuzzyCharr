class Employee:

    raise_amount = 1.04
    num_employees = 0

    def __init__(self, first, last, pay):
        self.first = first
        self.last = last
        self.pay = pay
        Employee.num_employees += 1

    def printAll(self):
        print(f'{self.first} {self.last}')

    @classmethod
    def set_raise_amt(cls, amount):
        cls.raise_amount = amount

class Manager(Employee):
    def __init__(self, first, last, pay, employees = None):
        Employee.__init__(self, first, last, pay)
        if employees is None:
            self.employees = []
        else:
            self.employees = employees

    def print_emps(self):
        for emp in self.employees:
            emp.printAll()
    
    def add_emp(self, emp):
        if emp not in self.employees:
            self.employees.append(emp)

    def remove_emp(self, emp):
        if emp in self.employees:
            self.employees.remove(emp)

dev_1 = Employee('Bob', 'Jenkins', 60000)
dev_2 = Employee('Andrew', 'Grant', 70000)

mgr_1 = Manager('Sue', 'Smith', 90000, [dev_1])
mgr_1.add_emp(dev_2)

mgr_1.print_emps()
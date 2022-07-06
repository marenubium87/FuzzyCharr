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

aerie = Employee('A', 'E', 5)
aerie.printAll()

Employee.printAll(aerie)
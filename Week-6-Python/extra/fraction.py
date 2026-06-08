class Fraction:
    def __init__(self, num, denom):
        assert type(num) == int and type(denom) == int
        self.num = num
        self.denom = denom
    
    def __str__(self):
        return str(self.num) + "/" + str(self.denom)
    
    def __add__(self, other):
        top = self.num * other.denom + self.denom * other.num
        bottom = self.denom * other.denom
        return Fraction(top, bottom)

    def __sub__(self, other):
        top = self.num * other.denom - self.denom * other.num
        bottom = self.denom * other.denom
        return Fraction(top, bottom)

    def __float__(self):
        return self.num/self.denom
    
    def inverse(self):
        return Fraction(self.denom, self.num)
    
a = Fraction(1, 4)
b = Fraction(3, 4)
c = a + b
print(c)
print(float(c))
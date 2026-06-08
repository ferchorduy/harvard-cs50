class Jar:

    def __init__(self, capacity=12):
        if not isinstance(capacity, int) or capacity <= 0:
            raise ValueError("Not a positive integer")
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        cookies = ""
        for _ in range(self._size):
            cookies += "🍪"
        if cookies == "":
            return "No cookies"
        else: return cookies

    def deposit(self, n):
        if n > self._capacity - self._size:
            raise ValueError("Not enough space in jar")
        self._size += n

    def withdraw(self, n):   
        if n > self._size:
            raise ValueError("Not enough cookies in jar")
        self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size
    
    @capacity.setter
    def capacity(self, n):
        print("Setter ran")
        self._capacity = n


def main():
    jar = Jar(20)
    print(str(jar.capacity))
    print(jar)
    jar.deposit(12)
    print(jar)
    jar.withdraw(5)
    print(jar)
    print(jar.capacity)
    print(jar.size)
    jar2 = Jar(20)
    jar2.capacity = 50
    print(jar2._capacity)


if __name__ == "__main__":
    main()
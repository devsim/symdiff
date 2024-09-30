from symdiff import newapi

for x in 'a + b + c', 'x * y * 3', 'x *':
    y = newapi.parse(x)
    print(y.get_status())
    print(y.get_string())
    print(y.get_error())



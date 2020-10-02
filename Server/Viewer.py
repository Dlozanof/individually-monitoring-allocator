class Entry:

    def __init__(self, name, timepoint):
        self.name = name
        self.data = [timepoint]
    
    def append(self, other):
        self.data.append(other.data[0])
    
    def __str__(self):
        return "{} ; {}".format(self.name, self.name)
    
    def get_name(self):
        return self.name
    
class Database:
    
    def __init__(self):
        self.db = []

    def append_data(self, csvinfo):
        data = csvinfo.strip().split(";")
        name = data[1]
        timeinfo = (int(data[0]), int(data[4]))

        if len(self.db) == 0:
            self.db.append(Entry(name, timeinfo))
        else:
            found = False
            for element in self.db:
                if element.name == name:
                    element.append(Entry(name, timeinfo))
                    found = True
            if not found:
                self.db.append(Entry(name, timeinfo))

db = Database()
with open("Server/output.csv") as f:
    for line in f:
        db.append_data(line)

for entry in db.db:
    print(entry.name)
    print(entry.data)

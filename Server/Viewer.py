import matplotlib.pyplot as plt
import argparse

# Options:
# Viewer.py --list:
# It will list all elements, easy to grep
# Viewer.py cmp1 cmp2
# It will only show data for those elements
# Viewer.py cmp1 cmp2 --noglobal -> Same but without global usage
# Viewer.py --only-stats -> Only show stats table, if components defined show only these
parser = argparse.ArgumentParser()
parser.add_argument("--list", help="List captured elements", action="store_true")
parser.add_argument("--filter")
args = parser.parse_args()

#components_of_interest = [args.cmp1, args.cmp2]

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
        timeinfo = (int(data[0]), int(data[3]), int(data[4]))

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


def populate_db(db):
    # Parse CSV data
    with open("Server/output.csv") as f:
        for line in f:
            db.append_data(line)


def list_elements(db):
        for element in db.db:
            print(element.name)
        

def prepare_filtered_plot(db, fig, ax):
    for entry in db.db:
        if entry.name in args.filter.split(","):
            ax.step([0] + [x[0] for x in entry.data], [0] + [x[1] for x in entry.data], label=entry.name, where='post')


def prepare_full_plot(db, fig, ax):
    for entry in db.db:
        ax.step([0] + [x[0] for x in entry.data], [0] + [x[1] for x in entry.data], label=entry.name, where='post')
    global_usage = [(x[0], x[2]) for entry in db.db for x in entry.data]
    global_usage.sort(key=lambda x: x[0])
    ax.step([0] + [x[0] for x in global_usage], [0] + [x[1] for x in global_usage], ':', label='global', where='post')


if __name__ == "__main__":
    # Populate database of entries, one array per element analyzed
    db = Database()
    populate_db(db)

    # Behavior 1: just list files
    if args.list:
        list_elements(db)
        exit(0)

    # Behavior 2: show filtered elements:
    if args.filter:
        fig, ax = plt.subplots()
        prepare_filtered_plot(db, fig, ax)

        plt.legend(title='SW Component:')
        plt.xlabel('Time (ns)')
        plt.ylabel('Heap usage (Bytes)')
        plt.title('Dynamic memory analysis')
        
        fig.show()
        input('Press a key to continue')
        exit(0)
    
    # behavior 3: show everything:
    fig, ax = plt.subplots()
    prepare_full_plot(db, fig, ax)
    
    plt.legend(title='SW Component:')
    plt.xlabel('Time (ns)')
    plt.ylabel('Heap usage (Bytes)')
    plt.title('Dynamic memory analysis')
    fig.show()
    input('Press a key to continue')
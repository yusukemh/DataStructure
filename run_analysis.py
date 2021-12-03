from subprocess import call, check_output

def run_command(command):
    # print(command)
    return check_output(command.split(' '))

top_dir = "testsets"
SET_TYPES = ["A-I", "A-D", "A-S", "B-I", "B-D", "B-S", "R"]
NUM_OPERATIONS = ["10000", "50000", "100000", "500000", "1000000"]
TREE_TYPES = ["st", "rbt", "treap"]

for set_type in SET_TYPES:
    for n_operations in NUM_OPERATIONS:
        for tree_type in TREE_TYPES:
            print(f"{set_type}-{n_operations}:{tree_type}")

            runtimes = 0
            for n_iter in range(1, 6):
                for _ in range(5):
                    res = run_command(f"./treap testsets/{set_type}/{n_operations}/iter_{n_iter}.txt")
                    runtime = res.decode("utf-8").split()[6]
                    runtimes += float(runtime)
            # print(f"Avg: {runtimes / 25}")
            print("AVG: {:.5f}".format(runtimes/25))

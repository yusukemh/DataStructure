from subprocess import call, check_output

def run_command(command):
    # print(command)
    return check_output(command.split(' '))

top_dir = "testsets"
TREE_TYPES = ["st", "rbt", "treap"]

if False:
    # Run analysis on ["A-I", "A-D", "A-S", "B-I", "B-D", "B-S", "R"]
    SET_TYPES = ["A-I", "A-D", "A-S", "B-I", "B-D", "B-S", "R"]
    NUM_OPERATIONS = ["10000", "50000", "100000", "500000", "1000000"]
    for set_type in SET_TYPES:
        for n_operations in NUM_OPERATIONS:
            for tree_type in TREE_TYPES:
                print(f"{set_type}-{n_operations}:{tree_type}")

                runtimes = 0
                for n_iter in range(1, 6):
                    for _ in range(5):
                        res = run_command(f"./{tree_type} testsets/{set_type}/{n_operations}/iter_{n_iter}.txt")
                        runtime = res.decode("utf-8").split()[6]
                        runtimes += float(runtime)
                # print(f"Avg: {runtimes / 25}")
                print("AVG: {:.5f}".format(runtimes/25))
if False:
    # Run Analysis on ["ST-1-U", "ST-1-N"]
    SET_TYPES = ["ST-1-U", "ST-1-N"]
    NUM_OPERATIONS = ["100000", "500000", "1000000", "5000000", "10000000"]
    for set_type in SET_TYPES:
        for n_operations in NUM_OPERATIONS:
            for tree_type in TREE_TYPES:
                print(f"{set_type}-{n_operations}:{tree_type}")

                runtimes = 0
                for n_iter in range(1, 6):
                    for _ in range(5):
                        res = run_command(f"./{tree_type} testsets/{set_type}/{n_operations}/iter_{n_iter}.txt")
                        runtime = res.decode("utf-8").split()[6]
                        runtimes += float(runtime)
                # print(f"Avg: {runtimes / 25}")
                print("AVG: {:.5f}".format(runtimes/25))
if True:
    # Run analysis on "H"
    set_type = "H"
    NUM_OPERATIONS = ["1000", "5000", "10000", "50000", "100000"]
    NUM_OPERATIONS = ["50000", "100000"]
    for n_operations in NUM_OPERATIONS:
        for tree_type in TREE_TYPES:
            print(f"{set_type}-{n_operations}:{tree_type}")
            heights = 0;
            for n_iter in range(1, 6):
                if tree_type == "treap":
                    # if treap, run five times because height is non-deterministic
                    for _ in range(5):
                        res = run_command(f"./{tree_type} testsets/{set_type}/{n_operations}/iter_{n_iter}.txt")
                        height = res.decode("utf-8").split()[11]
                        heights += int(height)
                else:
                    # if rbt or st, the tree is deterministic per instance
                    res = run_command(f"./{tree_type} testsets/{set_type}/{n_operations}/iter_{n_iter}.txt")
                    height = res.decode("utf-8").split()[11]
                    heights += int(height)
            if tree_type == "treap":
                print("AVG: {:.2f}".format(heights/25))
            else:
                print("AVG: {:2f}".format(heights/5))


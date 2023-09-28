import sys
import graphviz
import requests

packages = []


def getPackageName(requirement: str):
    for i in "(", ">", " ":
        if requirement.find(i):
            requirement = requirement.split(i)[0]
    return requirement


def getDependencies(package_name):
    if len(packages) >= 9:
        return

    content = {}
    content = requests.get("https://pypi.org/pypi/" + package_name + "/json").json()

    requirements = content["info"]["requires_dist"]

    if not requirements:
        return

    for i in range(len(requirements)):
        requirements[i] = getPackageName(requirements[i]).lower()

    requirements = set(requirements)

    for key in requirements:
        if package_name + " " + key not in packages:
            packages.append(package_name + " " + key)
            getDependencies(key)


def make_graph(graph):
    for package in packages:
        arr = package.split()
        if len(arr) == 2:
            graph.edge(arr[0], arr[1])


def main():
    name = sys.argv[1]
    if len(name) != 0:
        if getDependencies(name) != False:
            graph = graphviz.Digraph('Dependencies ' + name)
            graph.node(name)
            packages.append(name)
            make_graph(graph)
            graph.render(filename=name + ".gv")
            print("Граф зависимостей пакета " + name + " сохранен в " + name + ".gv и " + name + ".gv.pdf")

if __name__ == "__main__":
    main()

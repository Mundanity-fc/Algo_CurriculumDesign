from Louvain import Louvain


def SNAP():
    lou = Louvain('nodelist.txt')
    lou.getLabel('labellist.txt')
    lou.run()


if __name__ == "__main__":
    SNAP()

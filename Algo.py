from Louvain import Louvain

if __name__ == "__main__":
    lou = Louvain('nodelist.txt')
    lou.getLabel('labellist.txt')
    lou.run()

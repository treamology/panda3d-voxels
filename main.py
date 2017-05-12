from direct.showbase.ShowBase import ShowBase

from test import say_hello

class Main(ShowBase):
    def __init__(self):
        ShowBase.__init__(self)

        testModel = loader.loadModel("panda");
        testModel.reparentTo(render)

        say_hello()


if __name__ == "__main__":
    main = Main()
    main.run()
from SolarEnginePy import *
from SolarEnginePy import Application, ApplicationAdapter, Logger, Context
from SolarEnginePy.Window import Window
from SolarEnginePy.Graphics import Shape

from OpenGL.GL import *

# class Test(Application):
#     def setup(self):
#         print ("setup")
#
#     def start(self):
#         print ("start")
#
#     def stop(self):
#         print ("stop")
#
# test = Test()
# test.run()


class Game(ApplicationAdapter):
    def __init__(self, _context):
        super(Game, self).__init__(_context)
        self.window = Window(_context)
        self.graphics = None
        self.shape = None

    def setup(self):
        self.window.createWindow(width=900, height=700)
        self.window.setTitle("HI JACOB")
        self.graphics = self.getSubsystem(getGraphics())
        self.shape = Shape()

    def start(self):
        Logger.log_info(message="Starting game")

    def stop(self):
        self.window.close()

    def handleUpdate(self, event_type, params, **kwargs):
        return

    def handleRender(self, event_type, params, **kwargs):
        self.graphics.clearColor(0, 0, 0, 1)
        self.shape.render()
#

# def main(argv):
context = Context()
game = Game(context)
app = Application(context, game)
app.run()


# if __name__ == '__main__':
#     main(sys.argv)

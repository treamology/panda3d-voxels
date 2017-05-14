from direct.showbase.ShowBase import ShowBase
from panda3d.core import WindowProperties

from panda3d.core import loadPrcFileData
loadPrcFileData('', """
                win-size 1920 1080
                sync-video 0
                show-frame-rate-meter 1
                fullscreen 1""")


class Main(ShowBase):

    capturing_mouse = False

    def __init__(self):
        ShowBase.__init__(self)

        # Disable the default camera controls
        base.disable_mouse()

        # Controls for capturing and releasing the mouse
        self.accept("escape", self.release_mouse)
        self.accept("mouse1", self.capture_mouse)

        self.current_props = base.win.get_properties()

        self.setup_controls()

        # Load a test model
        test_model = loader.load_model("panda.egg")
        test_model.set_pos(0, 40, -5)
        test_model.reparent_to(base.render)

    def setup_controls(self):
        taskMgr.add(self.mouse_move_task, "MouseMovementTask")

    def mouse_move_task(self, task):
        if self.capturing_mouse:
            # Be sure mouse is inside the window, or else panda crashes if you try to get the mouse position.
            x, y = 0, 0
            if self.mouseWatcherNode.has_mouse():
                x, y = self.mouseWatcherNode.get_mouse_x(), self.mouseWatcherNode.get_mouse_y()

            # Move the pointer back to the center of the screen
            base.win.move_pointer(0,
                                  int(self.current_props.get_x_size() / 2),
                                  int(self.current_props.get_y_size() / 2))

            # Change camera angle based on mouse movement, being sure to constrain the pitch to keep the camera from
            # going upside down
            p = base.camera.get_p()
            if p + (y * 20) <= 90 and p - (y * 20) >= -90:
                base.camera.set_p(base.camera, y * 20)
            base.camera.set_h(base.camera, -x * 20)

            base.camera.set_r(0)

        return task.cont

    def capture_mouse(self):
        props = WindowProperties()
        props.set_cursor_hidden(True)
        props.set_mouse_mode(WindowProperties.M_confined)
        base.win.request_properties(props)

        self.capturing_mouse = True

    def release_mouse(self):
        props = WindowProperties()
        props.set_cursor_hidden(False)
        props.set_mouse_mode(WindowProperties.M_absolute)
        base.win.request_properties(props)

        self.capturing_mouse = False

if __name__ == "__main__":
    main = Main()
    main.run()

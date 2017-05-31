from direct.showbase.ShowBase import ShowBase
from panda3d.core import WindowProperties
from panda3d.core import loadPrcFileData

from voxel import Chunk
from voxel import World

import math

class Main(ShowBase):

    capturing_mouse = False

    def __init__(self):
        ShowBase.__init__(self)

        # Disable the default camera controls
        base.disable_mouse()

        self.current_props = base.win.get_properties()

        self.mouse_scale = 0.05
        self.win_size_x, self.win_size_y = self.current_props.get_x_size(), self.current_props.get_y_size()
        # Setup mouse and keyboard controls
        self.setup_controls()

        self.accept("window-event", self.window_updated)

        # Load a test model
        test_model = loader.load_model("panda.egg")
        test_model.set_pos(0, 40, -5)
        test_model.reparent_to(base.render)

        self.accept("chunk_progress", self.chunk_progress)
        self.world = World(64, 64, "blah", "chunk_progress")
        self.world.set_render_mode_wireframe()
        self.world.reparent_to(base.render)

    def chunk_progress(self, progress):
        print("Chunk progress" + str(progress))

    def generate(self):
        self.world.start_initial_generation()

    def delete_world(self):
        self.world.removeNode()
        del self.world

    def window_updated(self, win):
        super(Main, self).windowEvent(win)  # Send the window event up the chain
        self.current_props = base.win.get_properties()
        self.win_size_x, self.win_size_y = self.current_props.get_x_size(), self.current_props.get_y_size()

    def setup_controls(self):
        # Controls for capturing and releasing the mouse
        self.accept("escape", self.release_mouse)
        self.accept("mouse1", self.capture_mouse)

        # Movement controls
        self.accept("w", self.update_key, ["w", True])
        self.accept("w-up", self.update_key, ["w", False])
        self.accept("s", self.update_key, ["s", True])
        self.accept("s-up", self.update_key, ["s", False])
        self.accept("a", self.update_key, ["a", True])
        self.accept("a-up", self.update_key, ["a", False])
        self.accept("d", self.update_key, ["d", True])
        self.accept("d-up", self.update_key, ["d", False])
        self.accept("q", self.update_key, ["q", True])
        self.accept("q-up", self.update_key, ["q", False])
        self.accept("e", self.update_key, ["e", True])
        self.accept("e-up", self.update_key, ["e", False])
        self.accept("g", self.generate)
        #self.accept("d", self.delete_world)

        self.key_state = {"w": False, "s": False, "a": False, "d": False, "q": False, "e": False}
        taskMgr.add(self.controls_task, "MouseMovementTask")

    def update_key(self, key: str, state: bool):
        self.key_state[key] = state

    def controls_task(self, task):
        dt = globalClock.getDt()
        if self.capturing_mouse:
            # Be sure mouse is inside the window, or else panda crashes if you try to get the mouse position.
            x, y = 0, 0
            if self.mouseWatcherNode.has_mouse():
                # x, y = self.mouseWatcherNode.get_mouse_x(), self.mouseWatcherNode.get_mouse_y()
                # x *= self.current_props.get_x_size()
                # y *= self.current_props.get_y_size()
                # length = math.sqrt(self.current_props.get_x_size() ** 2 + self.current_props.get_y_size() ** 2)
                # x /= length
                # y /= length
                pointer = base.win.get_pointer(0)
                x, y = pointer.x, pointer.y

            # Move the pointer back to the center of the screen
            base.win.move_pointer(0,
                                  int(self.win_size_x / 2),
                                  int(self.win_size_y / 2))

            x -= int(self.win_size_x / 2)
            y -= int(self.win_size_y / 2)

            print(x, y)
            
            # Change camera angle based on mouse movement, being sure to constrain the pitch to keep the camera from
            # going upside down
            p = base.camera.get_p()
            if p + (y * self.mouse_scale) <= 90 and p - (y * self.mouse_scale) >= -90:
                base.camera.set_p(base.camera, -y * self.mouse_scale)
            base.camera.set_h(base.camera, -x * self.mouse_scale)

            base.camera.set_r(0)

        if self.key_state["w"]:
            base.camera.setY(base.camera, 30 * dt)
        if self.key_state["s"]:
            base.camera.setY(base.camera, -30 * dt)
        if self.key_state["d"]:
            base.camera.setX(base.camera, 30 * dt)
        if self.key_state["a"]:
            base.camera.setX(base.camera, -30 * dt)
        if self.key_state["q"]:
            base.camera.setZ(base.camera, 30 * dt)
        if self.key_state["e"]:
            base.camera.setZ(base.camera, -30 * dt)

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
    loadPrcFileData('', """
                    win-size 1280 720
                    sync-video 1
                    show-frame-rate-meter 1
                    fullscreen 0
                    want-pstats 0""")

    main = Main()
    main.run()

import kivy
from kivy.uix.widget import Widget
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.scrollview import ScrollView
from kivy.uix.button import Button
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.screenmanager import Screen, ScreenManager
from kivy.uix.checkbox import CheckBox
# from kivy.properties import ObjectProperty, StringProperty
from kivy.app import App
from kivy.clock import Clock
from serial.serialutil import Timeout
from arduino import Arduino

class ControllerScreen(Screen):
    pass


class CustomManager(ScreenManager):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.c = Arduino("COM6")


class CircuitControllerApp(App):
    def build(self):
        sm= CustomManager()
        sm.add_widget(ControllerScreen())
        return sm

if __name__=="__main__":
    CircuitControllerApp().run()
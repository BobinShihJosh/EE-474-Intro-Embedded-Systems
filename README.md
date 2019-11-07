
# Low-Cost touch screen Medical Monitering System
![alt text](https://github.com/BobinShihJosh/EE-474-Intro-Embedded-Systems/blob/master/Project%204/image2.png)
## Project Specifications:
This project is the first phase in the development of a low cost, portable, medical monitoring
system. The current phase focuses on the design and development of the basic system
architecture, modeling the instrumentation, establishing the high-level control flow, and
managing the basic switching operations, display, and alarm and warning annunciation
functions. The initial deliverables include the high-level system architecture, the ability to
perform a subset of the necessary control, and portions of the display and annunciation
components. Subsequent phases will continue to evolve the system architecture and flow of
control, extend the driver development, and incorporate additional capabilities into both the
measurement and display subsystems.
The final subsystem must be capable collecting data from several different types of sensors,
processing the data from those sensors, displaying it locally, and then transmitting it over a
local area network to a collection management station.
In developing such a system, we will,
1. Introduce formal specifications
2. Introduce and work with formal design methodologies such as UML - Use Cases,
Functional Decomposition, Sequence Diagrams, State Charts, and Data and Control
Flow Diagrams.
3. Work with the C language.
4. Develop and build your background on C pointers, the passing of pointers to
subroutines, and manipulating them in your subroutines.
5. Introduce simple tasks and a task queue.
6. Share data between tasks.
7. Use software delay/timing functions.
8. Use basic output operations. 
System Requirements Specification
1.0 General Description
A low cost, state of the art medical monitoring and analysis system is to be designed and
developed. The following specification elaborates the requirements for the display and alarm
portion of the system.
The measurement, display, and alarm management subsystems must accept inputs from a
number of sensors used to collect data from various parts of the human body and signal a
warning if the data falls outside of pre-specified bounds. Some analysis of the data will be
performed by other parts of the system to be designed later.
The outputs of the sensors that are measuring a variety of natural phenomenon comprise a
number of different data types such as integers, strings or high precision numbers. The
system must be designed to accommodate each of these different types. 
- 5 of 18 -
1.1 Monitoring Subsystem
Displayed messages comprise three major categories: annunciation, status and warning /
alarm. Such information is to be presented on the local TFT display on the front panel on the
ATMega microcomputer.
The local display function will be partially developed during this phase, but will be fully
incorporated during follow-on phases.

1.2 Measurement and Display Subsystems
Measurements will be modeled, as appropriate, in each of the respective tasks in the System
Control portion of the System. Modeled sensor signals are to be continuously monitored
against predetermined limits. If such limits are exceeded, a visible indication is to be given
and shall continue until acknowledged.
Acknowledgement shall be indicated but a visible indication shall continue until the aberrant
value has returned to its proper range. If the signal value remains out of range for a specified
time, the original annunciation shall recommence.
System Inputs
The measurement component of the system in the first prototype must track and support
the measurement of the following signals:
Measurements
Blood Pressure
Body temperature
Pulse rate
System Outputs
The display component of the system must track and support the display of the following
signals:
Display
Blood Pressure
Body temperature
Pulse rate
The status, alarm, and warning management portion of the system must monitor and
annunciate the following signals:
Status
Battery state
Alarms
Temperature, blood pressure, or pulse rate too high
Warning
Temperature, blood pressure, or pulse rate out of range 

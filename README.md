# Air-Powered Robotics

## Overview
We are designing and constructing a soft snake robot using components such as McKibben muscles and other pneumatic components made from dragonskin and reinforced muscles. The goal is to explore small and inaccessible spaces with a deformable robot that can more easily navigate them.

To support and enable the acuation of this robot, we designed and built a parallelized pneumatic actuation manifold consisting of 5 units each capable of alternating between closed state, open state, vacuum state, and air pressure state with and without power to an air pump. The supporting code is located at https://github.com/ThePenultimatum/softRoboticsProject where I have written a programming interface to the microcontroller so that the states can be changed by referencing sets of valves and states instead of changing special function registers or pins on the microcontroller.

The microcontroller we used is the PIC32. It is on an NU32 board designed and built by faculty and staff at Northwestern University.

[View the project on github here.](https://github.com/ThePenultimatum/softRoboticsProject)

## Components

* 1 NU32 board with PIC32 microcontrollers (1 per node including central node)
* 4+ ft<sup>2</sup> Acrylic sheets for chassis
* 5 Air pumps
* 20 Pneumatic solenoid valves
* 2 Long breadboards (the default common size is okay)
* 20 feet of solid core wire (ideally in separate colors for organization)
* Electrical Tape
* Wire cutters and wire strippers
* Assorted screws, nuts, bolts, washers
* Hot Glue, caulk, or epoxy

## Implementation

### Design

#### Manifold

##### Air-Vacuum Module

##### Chassis

#### MMVS-McKibben Robot

##### MMVS

##### McKibben

##### Interface Connector

## Resources:

* "Embedded Computing and Mechatronics with the PIC32 Microcontroller" Textbook
* Soft Robotics Toolkit

## Contributing

If contributing to the modifications in our project here, please follow the following steps:
* Fork the repository
* Add your modifications to either the dev branch or a branch off of the dev branch
* Make a pull request with informative descriptions

## Ongoing Development

Current work:
* Streamlining electrical components and connections on pneumatic manifold
* Gait development for MMVS-McKibben combination robot

## Team

* **Mark Dyehouse** -[ThePenultimatum](https://github.com/ThePenultimatum)
* **Andrew Thompson** -[mossti](https://github.com/mossti)
* **Victor Stepanov**
* **Yuchen Wang** -[yuchnw](https://github.com/yuchnw)
* **Joel Meyer**
* **Ethan Park**

## License

## Acknowledgments

* Dr. Mitra Hartmann (Northwestern U.)
* Bill Hunt (Northwestern U.)
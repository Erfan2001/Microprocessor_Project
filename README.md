 # Microprocessor Project
 
 Design of a two-stroke traffic light control system by a microcontroller

## Project description:

The objective is to devise a dual-phase traffic light control system for a single intersection, leveraging a microcontroller. This entails considering the utilization of 32 Atmega six microcontroller outputs to facilitate the management of two traffic lights, with each traffic light comprising three diodes for green, yellow, and red signals.

Additionally, the system incorporates two potentiometers, characterized by voltage values ranging from zero to 5 volts, to regulate the duration of the light phases. These two potentiometers are integrated with the analog-to-digital microcontroller unit as input sources.

The first potentiometer governs the overall duration of a complete cycle encompassing green, yellow, and red light phases, all measured in seconds. This parameter is adjustable, allowing for customization of the maximum and minimum time limits as per specific requirements.

On the other hand, the second potentiometer assumes the role of determining the distribution ratio of green light time between both sides of the intersection. To elucidate, when the second potentiometer is set to its midpoint (2.5 volts), an equal green time is allocated to both sides of the intersection. This ratio can be dynamically increased or decreased, offering flexibility in managing the durations. Customizable upper and lower thresholds for this ratio are also available for selection.


 *Implemented By Erfan Nourbakhsh*
 
 *Spring 2022*

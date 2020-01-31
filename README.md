## Plague Simulator
This program consist of a python front-end front.py and executable backend written in C++. Transmission of pathogen among a population with 2D simple random walk and jump behaviour is simulated. Python 3 with matplotlib package installed is required for running the front-end script.<br><br>
Press any key to continue the simulation, mouse click to end simulation and show statistics overtime. The follwing is a list of parameters you can modify in the file front.py<br>
#### Float Type:
COUGHT_MARGIN: The level of severity where coughing symptom appear, coughing can double the transmission range for airbrone pathogen.<br>
PROGRESS_RATE: The rate of which the severity of disease progress, the health reduction of infected people in each iteration is proportional to severity.<br>
TRANSFER_PROB: The probablity of healthy people get infected in each iteration when they are close to infected individuals.<br>
MASKED_RATIO: The proportion of people waring mask. Either the healthy person or pathogen carrier wear mask, the probability of infection reduce by half.<br>
JUMP_PROB: Probability for a random jump to occur for any individuals in each iteration, random jumps have no distance limit.<br>
#### Integer Type:
MAP_SIZE: The side length of square that population is generated on, there is no map size limit after the simulation starts. <br>
POPULATION_SIZE: Number of individuals in the population.
RANGE: The range which the pathogen can trasfer.<br>
#### Boolean Type (1 true, 0 false):
CORPSE_HANDLE: If true, dead individuals are taken cared of. Otherwise, they remain infective.<br> 
AIRBRONE: If true the pathogen is airbrone. Airbrone pathogen togather with coughing symptom have double range.<br> 
RANDOM_PROGRESS: If true, the change of severity follow Normal(PROGRESS_RATE, PROGRESS_RATE). Otherwise, severity increase constantly with PROGRESS_RATE.
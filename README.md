 <center><h2><ins>Gradient-descent-for-Runst</ins></h2></center>

The program here is the adaptation of Josh Starmer's video:
[![here](https://img.youtube.com/vi/sDv4f4s2SB8&t/0.jpg)](https://www.youtube.com/watch?v=sDv4f4s2SB8&t)

___

As I am blocking at coding the backpropagation algorithm in this video:
[![here](https://img.youtube.com/vi/GKZoOHXGcLo&t/0.jpg)](https://www.youtube.com/watch?v=GKZoOHXGcLo&t)
And as I am indeed going totally bonkers I have to step back and rethink what I have learned so far.

To be 100% sure of what is about gradient descent I will try to explain it.

But I will also try to make some hypotheses of what should be added to the gradient descent algorithm to work in a neural network, at least the one in the video mentioned earlier...

<ins>The goal of gradient descent:</ins>\
The goal of gradient descent is to determine the intercept and the slope of a "prediction line", here the line predict the <span style="color:blue">height</span> of someone by giving her or his <span style="color:red">weight</span>.

But the algorithm need some samples in order to have a grasp of how this line must look, in terms of intercept and slope, those sample are the given <span style="color:red">weight</span> of three peoples and their observed <span style="color:blue">height</span>.

First, the algorithm will have a given initial guess, those are stored in ```slope_intercept```, there are initialised as two <span style="color:green">0</span> but they can be others values like negative one or even randomly declared.

With the guest value of the slope (<span style="color:green">0</span>) and the intercept (<span style="color:green">0</span>) the algorithm will create a <span style="color:green">line of "prediction"</span> on a xy axis. The algorithm will also put some dot which shows the three samples (peoples) on the axis with: 
$$\color{red} x = given_-value = weight \color{black} \quad \textrm{ and } \quad \color{blue} y = observed_-value = height$$

<p align="center">
    <img src="images/begining.png" width="450"/>
</p>



In a neural network...

how to fit the line to the. data, least square


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
The goal of gradient descent is to determine the intercept and the slope of a "prediction line", here the line predict the $\color{blue}height$ of someone by giving her or his $\color{red}weight$.

But the algorithm need some samples in order to have a grasp of how this line must look, in terms of intercept and slope, those sample are the given $\color{red}weight$ of three peoples and their observed $\color{blue}height$.

First, the algorithm will have a given initial guess, those are stored in ```slope_intercept```, there are initialised as two $\color{green}0$ but they can be others values like negative one or even randomly declared.

With the guest value of the slope ($\color{green}0$) and the intercept ($\color{green}0$) the algorithm will create a $\color{green} \textrm{prediction line} $ on a xy axis. The algorithm will also put some dot which shows the three samples (peoples) on the axis with $\color{red} x = given_-value = weight$ and $\color{blue} y = observed_-value = height$:

<p align="center">
    <img src="images/begining.png" width="450"/>
</p>

The goal of this algorithm is to change the position of the $\color{green} \textrm{prediction line}$ to minimize as much as possible the difference between $\color{blue} y  \color{red}_{\textrm{given-value}}$ and $\color{blue} y \color{green}_{\textrm{prediction line}}$ (the difference between  $\textrm{\color{blue} the observed value \color{red}from the given value}$ and $\textrm{\color{green}what the algorithm should \color{blue}find \color{red}from the given value}$) ```for``` each samples:

<p align="center">
    <img src="images/substraction-correction.png" width="450"/>
</p>

Now we know for each samples how much the $\color{green} \textrm{prediction line}$ fit to $\textrm{\color{blue}the observed value}$. 
But we want to know from a general perspective how much the $\color{green} \textrm{prediction line}$ fit to $\textrm{\color{blue}the observed values}$, to do so we sum up all of the differences calculated. 

___
<center><ins>Note:</ins></center>

Sometimes the $\color{green} \textrm{prediction line}$ may look like this:

<p align="center">
    <img src="images/note1-correction.png" width="450"/>
</p>

If we make the sum of the difference we will get: $$\textrm{sum} = 0.871 + (-0.531) + 0.135$$ $$=> \textrm{sum} = 0.475$$

But that doesn't make sense because the result is lower than the difference between $\color{blue} 1.4$ and $\color{green} 0.529$, which is $0.871$, adding the others differences lower it instead of increase it.

The solution to this is to make sure the diffrences are positive by calculating the square of the negative one: $$\textrm{sum} = 0.871 + (-0.531)^2 + 0.135$$

But we also need to calculate the square of positive differences to keep a sense of proportionality between the differences: $$\textrm{sum of squares} = 0.871^2 + (-0.531)^2 + 0.135^2$$ $$=> \textrm{sum of squares} = 1.059$$

<center><ins>End of the note</ins></center>

___

The sum of square for the main exemple:
$$\textrm{sum of squares} = (1.4)^2 + (1.9)^2 + (3.2)^2$$ $$=> \textrm{sum of squares} = 15.81$$

Now that we have the sum of square we can put it in another graph, a 3D one:


But to keep the thing simple 


$$\textrm{step size} = \textrm{sum of squares} * \textrm{learning rate}$$

$$\textrm{new value} = \textrm{value} - \textrm{step size}$$

In a neural network...

___
<center><ins>Additional note:</ins></center>

Values were the good intercept and slope are found (approximately):
(note: the prediction line found by Josh is: $y = a0.64 + 0.95$)
|$(o - p)^x$ only if x is even | Learning rate slope, weight | Learning rate intercept, bias | number of try | prediction line |
|---|---|---|---|---|
|$x = [2 ; 10]$| $0.01$ | $0.1$ | $$x = 2 => 108$$ $$x = 4 => 45$$ $$x = 6 => 22$$ $$x = 8 => 14$$ $$x = 10 => 76$$| $$x = 2 => y = a0.6402976217775229 + 0.9504417536953271$$ $$x = 4 => y = a0.6407941148661322 + 0.9492692569668632$$ $$x = 6 => y = a0.6411193057119328 + 0.9484918184754438$$ $$x = 8 =>  y = a0.6410162537466007 + 0.9487414252781016$$ $$x = 10 => y = a0.6412632970776748 + 0.9481394245821886$$|
|$x = [4 ; Idk]$| $0.001$ | $0.01$ | $$x = 4 => $$ $$x = 6 => $$ |
|||||
|||||
---
layout: mainpage
title: Realization
position: 4
---

# Realization

In the following sections I'll chronologically present excerpts of the in-between steps that let me to the final implementation.

![Notes during programming]({{ "/static/images/realization-1.gif" | prepend: site.baseurl }})
*Notes during programming*

## Cinder – Flocking Tutorial

After following Cinder's basic [Getting Started](https://libcinder.org/docs/guides/opengl/index.html) guide I took upon myself to implement the unfortunately out-dated Flocking Tutorial by [Robert Hodgin](http://www.roberthodgin.com/) with the latest version of Cinder. You'll find the tutorial under [Guides](https://libcinder.org/docs/guides/index.html). It is a two-part tutorial. [Part 1](https://libcinder.org/docs/guides/tour/hello_cinder.html) explains some Cinder basics and builds a basic particle simulation. Whereas [part 2](https://libcinder.org/docs/guides/flocking/chapter1.html) goes into the details of extending the particle simulation and also the implementation of steering behaviors.

Unfortunately with release v0.9.0 of Cinder the sample code of the tutorial was removed from the download. But for reference it is still available with older releases. Head of to Cinder's [Download](https://libcinder.org/download) page and download the release v0.8.6. Once unpackaged inside the relase folder you'll find a folder named tour which contains the original tutorial in HTML and also the source code for each chapter.

While adopting the tutorial for the latest version of Cinder I tried to apply as many concepts I learned from the introductory guide. Also I sometimes ventured into building my own variantions. The results of this exploration can be found in my GitHub repository [cinder-flocking-tutorial](https://github.com/davidbeermann/cinder-flocking-tutorial).

![Screenshot of Cinder flocking application]({{ "/static/images/cinder-flocking-tutorial.png" | prepend: site.baseurl }})
[*Final rendition of the Cinder flocking application*]({{ "/static/images/cinder-flocking-tutorial.png" | prepend: site.baseurl }})

Although the tutorial taught me a lot about Cinder in general and C++ and OpenGL specifically I had to find out that the [Cinder's extension for Kinect](https://github.com/cinder/Cinder-Kinect) does currently not work the latest version. One of the reasons was that Cinder switched from their on math library to [GLM](http://glm.g-truc.net/). While errors resulting from this change would be easily fixed, I also ran into other issues I was unable to resolve. Since I knew from the start that my project would rely on the Kinect camera I went on to work with openFrameworks.

## Examples

### Perlin Noise

Although I worked with Perlin Noise before I build a little graphing example to refamiliarize myself with its parameters. The result of that is the [Understanding Noise](https://github.com/davidbeermann/timely-matter/tree/master/examples/UnderstandingNoise) example.

![Screenshot of 'Understanding Noise' example application]({{ "/static/images/realization-understanding_perlin_noise_example.png" | prepend: site.baseurl }})

But that was more a finger exercise than anything really useful. Ultimately I wanted to write a class that would output two-dimensional perlin noise pixel data. My intention was to create an alternative input for debugging, so I'd be able to work on code without having to connect a Kinect – really useful when working on trains etc. Quickly I realized that doing the calculations and pixel buffer updates on the CPU was way to slow. So I had write a OpenGL shader program in order to generate the same output on the GPU. At first I'd find an of-the-shelf solution for this in no time. But turned out that I was either checking the wrong resources or it did not exist in the form that I needed it. 

After doing some research and tutorials I finally managed to get it up and running. The code can be found in the [Perlin Noise Shader](https://github.com/davidbeermann/timely-matter/tree/master/examples/PerlinNoiseShader) example.

![Screenshot of 'Perlin Noise Shader' example application]({{ "/static/images/realization-perlin_noise_example.png" | prepend: site.baseurl }})

### Marching Squares

In order to analyze the input from the Kinect camera and calculate the vectors pointing away from lighter (closer) areas I resorted to the [marching squares algorithm](https://en.wikipedia.org/wiki/Marching_squares). The algorithm is used to find the contour lines in a two-dimensional scalar field. So the idea was to place a grind of measuring points on top of the Kinect pixel data and find all contour lines that where higher than a certain threshold. From the contour lines I then calculated the perpendicular lines with I then used as vector pointing away from the inner white area.

{image_of_example}

So far this solution worked out fine. But then I had to find another algorithm which would assign vector forces to all inner, white quadrants in my segmented input data. For this purpose I first looked into the [flood fill algorithm](https://en.wikipedia.org/wiki/Flood_fill). The problem with this algorithm was that it started from a random location inside the contour line and then iteratively looked at its surrounding segments. Since I only had forces assigned to outer, contour segments and all of the inner segments should be derived from the closest contour vectors this algorithm did not work out initially.

An idea was to keep track of all contour segments during the execution of the marching square algorithm. Then I'd look at all surrounding, inner segments and store them with the association to the contour vectors. Then I'd calculate the vector based on all associated contour vectors. This then would yield another list of segments which run through the same routine as the contour segments until there were no inner segments left. Although possible in theory the implementation proved to fairly complex. And since I needed this code to run fast and efficiently at at least 30 frames per second I looked into alternatives.

My next candidate then were path finding algorithms, namely [Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) and [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm). The idea here was to find the closest contour segments for each inner segment. Though it would work to 'walk' from inside segments towards contour segments then the problem remained to assign forces from the outside segments to the inner ones. After some initial experimentation I became convinced that my initial instinct to choose the marching square algorithm was flawed and the reason for the problem I was running into down the road. So I went back to my initial problem and searched for solutions.

### Vector Field

After my problems with the marching squares approach another solution turned out to be right in front of my nose all along: vector fields or flow fields. Although I did not immediately find the reference that I was working with from the start. Before that I found an [example for openFrameworks](https://github.com/ofZach/algo2012/tree/master/other/vectorField_wParticles) of a [course on algorithmic animation](https://github.com/ofZach/algo2012) by [Zach Lieberman](http://thesystemis.com/). Ultimately I arrived back at [Daniel Shiffman](http://shiffman.net/)'s book [Natur of Code](http://natureofcode.com/book/) where in the [chapter 6 on Autonomous Agents](http://natureofcode.com/book/chapter-6-autonomous-agents/) writes at length about [Flow Fields](http://natureofcode.com/book/chapter-6-autonomous-agents/#66-flow-fields).

After implementing my own vector field from scratch based on the two aforementioned resources I was finally on the right track. The solution proved to be flexible and with very good performance. The version demonstrated below is already a little bit more complex than the [Simple Vector Field](https://github.com/davidbeermann/timely-matter/tree/master/examples/SimpleVectorField) example provided in my repository. The main difference is that the video also demonstrates a working particle system that is connected to the results of the vector field.

<iframe src="https://player.vimeo.com/video/179483028" width="640" height="360" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>

After discovering Shiffman's book I started a separate repository for my ['The Nature of Code' implementation for openFrameworks](https://github.com/davidbeermann/openframeworks-nature-of-code). This repository is very incomplete since it only features some code example from chapter 6. But I'll definitely return to this repository to continue implementing other examples. In case you're looking for more complete implementations there are [many more](https://github.com/search?utf8=%E2%9C%93&q=nature+of+code+openframeworks&type=Repositories&ref=searchresults) people who approached the endeavour more thoroughly.

### Homography

After having figured out the shader to generate perlin noise as my input for the vector field, I had to face the issue how to grab only the Kinect depth data in the area I was projecting onto. I needed a solution that I could easily adjust to different setups and locations. Otherwise I would have to change my code everytime I use a different projector or setup the installation in a different space. The solution I ended up using was a [homography](https://en.wikipedia.org/wiki/Homography), also called projective transformation.

The advantage of using this transformation is that any polygon described by four points can be transformed into another polygon of four points. This property really worked in my favor because I could not only extract a specific area in my depth data but also straighten the source data into a rectangle, which had the same properties as the pixel image generated by my perlin noise shader programm. Thereby the two methods were became interchangeable which allowed my to easily switch between the two at runtime.

The image below is a screenshot of my [OpenCV Homography example](https://github.com/davidbeermann/timely-matter/tree/master/examples/OpenCvHomography). This example shows the a slightly more complex application of the principle than I needed. There are two homography transformations applied where the output of the first transformation becomes the input of the second transformation. I wrote this slightly more complex example – including the custom UI elements to define the homography points – because I felt that this would visualize the power of this mathematical principle most clearly.

![OpenCV Homography example]({{ "/static/images/realization-open_cv_homography_example.png" | prepend: site.baseurl }})

The example is based in the openFrameworks addon [ofxCv](https://github.com/kylemcdonald/ofxCv) by [Kyle McDonald](http://kylemcdonald.net/), who wrote a fast and accessible implementation of the homography transformation.

### Programmable Geometry Shader

In preparation for the final visualization of the particle system I started to delve deeper into OpenGL shader programming. Of specific interest to me was the geometry shader stage in the graphics pipeline. It would allow me to handle only simple point data on the CPU and generate complex parametrized geometry on the GPU. Therefore I came up with a slightly more complex [Geometry Shader example](https://github.com/davidbeermann/timely-matter/tree/master/examples/ProgrammableGeometryShader). On the repository page I also list the resources I used while creating this example.

![Geometry Shader example]({{ "/static/images/realization-geometry_shader_example.png" | prepend: site.baseurl }})

## Working Prototype

This video is a complete walkthrough of the setup configuration and the interaction between the fabric and the projection. The first part demonstrates the configuration. The infrared (IR) needs to masked during the setup of the homography transformation id order to get a better camera image without the pseudo-random IR pattern in it. Once the setup is finished I show the mapping of the 3D depth data to the projection by projecting the depth buffer onto the fabric. This demonstrates how the interaction with the fabric is mapped to the depth data visually. In the last part I demonstrate how the depth data is powering a particle system through the use of a vector field. The particle system of the projection is not the final visualization.

<iframe src="https://player.vimeo.com/video/182398565" width="640" height="360" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>
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

While adopting the tutorial for the latest version of Cinder I tried to apply as many concepts I learned from the introductory guide. Also I sometimes ventured into building my own variantions. The results of this exploration can be found in my GitHub repository [Yet to be uploaded]().

[![Screenshot of Cinder flocking application]({{ "/static/images/cinder-flocking-tutorial.png" | prepend: site.baseurl }})]({{ "/static/images/cinder-flocking-tutorial.png" | prepend: site.baseurl }})
*Final rendition of the Cinder flocking application*

Although the tutorial taught me a lot about Cinder in general and C++ and OpenGL specifically I had to find out that the [Cinder's extension for Kinect](https://github.com/cinder/Cinder-Kinect) does currently not work the latest version. One of the reasons was that Cinder switched from their on math library to [GLM](http://glm.g-truc.net/). While errors resulting from this change would be easily fixed, I also ran into other issues I was unable to resolve. Since I knew from the start that my project would rely on the Kinect camera I went on to work with openFrameworks.

## openFrameworks — Nature of Code

* [The Nature of Code](http://natureofcode.com/) by [Daniel Shiffman](http://shiffman.net/)  
While you can buy the book you can also [read it online](http://natureofcode.com/book/) for free.  
Although written for Processing I set myself the goal to translate the presented concepts to openFrameworks – a project which [many](https://github.com/search?utf8=%E2%9C%93&q=nature+of+code+openframeworks&type=Repositories&ref=searchresults) have done before.

## Marching Squares

...

## Vector Field

...

## Homography

...
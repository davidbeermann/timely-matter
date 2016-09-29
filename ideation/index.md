---
layout: mainpage
title: Ideation
position: 1
---

# Ideation

Derived from the topics outlined under motivation several possible ideas for a practical implementation emerged. But the processes where never separate. It undulated back and forth between reading and ideation. Ideas came from research and inspired further research. It is probably unnecessary to point this out since it is common sense anyway. What I deem important though is that reading and writing were instruments in order to understand my own ideas. In a way, to crystalize them. In order to a crystal to be created it needs time and pressure. Staying in this metaphor reading was my investment of time and writing the compression of the inspiration I gained from it. Therefore my ideas are mostly in form of text and not visual. Instead of visualizing ideas I used words to capture them.

![Thoughts from notebooks]({{ "/static/images/ideation-1.gif" | prepend: site.baseurl }})
*Thoughts from notebooks*

Specific ideas usually developed around a concrete topics. The following descriptions provide a brief introduction to the relevant topics which were discarded.

## First Approach: Proverbs

There are many proverbs that deal with time directly or metaphorically. In some way or another these proverbs characterize how we perceive time. Here's an exemplary list of selected proverbs and idioms that acted as reference points during my research:

* Time is money.
* Time flies when you're having fun.
* The early bird catches the worm.
* Time is of the esscence.
* Life is short and time is swift.
* No time like the present.
* Time heals all wounds.
* Time and tide wait for no one.
* Wasting time is robbing oneself.
* Everything has its time.
* An ounce of gold will not buy an inch of time.
* Lost time is never found again.

Since this was an idea that was present from the very beginning of my thesis project, it was mostly founded on a feeling that these proverbs could be staged in a humurous way in order to make a comment on our strange relationship with the intangible matter of time. One of my visual reference points was the painting [*Nederlandse Spreekwoorden*](https://en.wikipedia.org/wiki/Netherlandish_Proverbs) by the dutch painter [Pieter Bruegel the Elder](https://en.wikipedia.org/wiki/Pieter_Bruegel_the_Elder). It depicts approximately 112 proverbs and idoms in smaller scenes within the whole painting. In sum it creates a utopian scene of human folly.

![The Dutch Proverbs]({{ "/static/images/prio_art-pieter_brueghel_the_elder-the_dutch_proverbs.jpg" | prepend: site.baseurl }})
[Image by the Google Art Project](https://en.wikipedia.org/wiki/File:Pieter_Brueghel_the_Elder_-_The_Dutch_Proverbs_-_Google_Art_Project.jpg)

Especially one tangent I was exploring in depth: the notion that these proverbs and idioms allude to some kind of materiality of time. Sometimes the association is literal – time is money – while other proverbs could be interpreted in many ways – i.e. in 'time heals all wounds' time could be a creme, alcohol or a bandage.

Although I really liked this humurous approach, in the end I had to amid to myself that the ideas I came up didn't work out as I anticipated. Especially the connection between time and technology proved to be a hurdle. So I followed another idiom: kill your darlings!

## Second Approach: Smell

Our sense of smell has a strong connection to our memory. While it might be hard to remember and visualize a certain moment in time, smell can immediately displace you emotionally into that very moment. This powerful influence on our perception I sought out to exploit.

Two projects where influencal when conceiving this idea. The [Smell Memory Kit](http://smellmemorykit.supersense.com/) by [SUPERSENSE](http://the.supersense.com/) from Vienna. The project uses abstract smells that you can carry with you in a small capsule. Everytime you like to memorize a moment you can break one capsule and take a deep breath. The project uses the principle explained above in a literal way: use smell to trigger one's memorization. Another inspiration was the work by [Sissel Tolaas](https://en.wikipedia.org/wiki/Sissel_Tolaas). Tolaas' works revolve exclusively around smells and scents. Moer on here work [here](http://www.sightunseen.com/2009/11/sissel-tolaas-scent-expert/) and [here](https://www.researchcatalogue.net/view/?weave=1036).

My idea pivoted around the speculative approach to 'smell the future'. In essence the concept was to use artificial smells with no memory connection in order to foster and 'memorize' new ideas for the future. In anticipation of these ideas connected to the smell they were more likely to become reality. The inspiration for this idea came from the notion that the future has caught up with the present due to the acceleration of time. Therefore the project's aim would have been to reclaim the future and mediate a positive outlook.

![Ideation for modular geometric object]({{ "/static/images/ideation-second_approach_smell.jpg" | prepend: site.baseurl }})
*Ideation for modular geometric object*

In terms of realizing this project I imagined to create objects which were uncommon in our common perception of space. They should create visual break and entice interaction. In order to accomplish this the idea was to write software to create abstract shapes through iteration over basic geometric objects. The software should have in addition also made sure that these objects could be produced out of modular components. Through talks with workshop leaders and other students knowledgable about such production techniques I imagined to produce these objects with [Rhino](http://www.rhino3d.com/) and [Grasshopper](http://www.grasshopper3d.com/) plus some Phyton scripting.

Inside of these objects I imagined to work not only with smell but also with light and sound and possibly even small computer screens in pursuit to create a multi-sensory experience. Some concrete ideas in this direction where developed. Ultimately I discarded the whole endeavor due to the complexity of production, material and production costs – ideally I wanted to build one object out of mirror glass – and time constraints.

![Notes on paper]({{ "/static/images/ideation-2.gif" | prepend: site.baseurl }})
*Notes on paper*

## Final Approach: Generative Systems

After my two initial approaches failed to yield a feasible idea for my thesis project I approached my ideation from different angle. Instead of extracting themes from theory and come up with ideas for implementations I pivoted by 180°. I simply started to think of installation setups from a purely visual standpoint and tried to associate these ideas with my theoretical background. It was all triggered by a review on [Ken Okiishi](http://www.pilarcorrias.com/artists/ken-okiishi/)'s work gesture/data in [Spike](http://www.spikeartmagazine.com/en) #47.

> A simple premise often works best in the execution of formal concerns.
> 
> Spike (p.181)  
> issue #47, The Body, Spring 2016

Back then I was already immersed with my theme for a long time. But suddenly my formal concerns started to align with my visual ideas more easily. At the time I was reading a text by Henri Bergson which yielded an association with an essay by Jon McCormick on emergence. And since I had an interest in gaining experience in C++ creative coding libraries and OpenGL programming these tendencies converged in the final idea for my project.

In the process that followed I constantly switched between implementation and theory in order to develop the idea further. Most of the technical and visual outcome I developed into example applications. These applications were published alongside the actual application on GitHub. Building my work on so much prior work done by people in the community quickly yielded the idea to publish the whole project under an Open Source licence. Writing and publishing code and my writing quickly and continuously under the same paradigm yielded huge boost in motovtion but also focus for me. Therefore I started to develop a workflow for this and my future projects which I'll make available publically.

## Prior Art

Here are some visual reference projects that were relevant in the context of developing my thesis idea.

### Lunar Surface

The work by [Kimchi and Chips](http://kimchiandchips.com/) uses a vertical flag of fabric which is moved by the wind. Its movement is tracked with a 3D camera which affects a projection onto the fabric. The projection is the outline of a sphere which relates to the actual position of the fabric in space. Through long exposure photography a fragmentary recreation of the virtual shape is created in actual space.

The project was not only relevant for me in terms of its visual outcome and approach. Also [Elliot Woods](https://github.com/elliotwoods?tab=repositories) is an avid educator and contributor to open source projects like openFrameworks. Many of his published resources helped me to advance my own work.

![Lunar Surface]({{ "/static/images/prior-art-kimchi-chips-lunar-surface.jpg" | prepend: site.baseurl }})
*Picture by Kimchi and Chips*

### Being not truthful

Being a longtime fan of [Stefan Sagmeister](http://sagmeisterwalsh.com/)'s work I immediately remembered his collaborative project with [Ralph Ammer](http://www.ralphammer.de/) for the project [Things I Have Learned In My Life So Far](http://sagmeisterwalsh.com/work/all/things-i-have-learned-in-my-life-so-far/). The projected illustration reacts to bypassing visitors by tracking their movement with a 3D camera. The responsiveness and naturalness of the installation where I benchmark I set for myself to live up to.

<iframe width="560" height="315" src="https://www.youtube.com/embed/U--PIzSuOv8" frameborder="0" allowfullscreen></iframe>

### Wide White Flow

Recommended to me by [Dennis Paul](http://dennisppaul.de/) this work by Hans Haake became a reference point im terms of its simplicity. This huge piece of fabric is floating in space through the wind produced by ventilators at one end of the installation.

![Wide White Flow]({{ "/static/images/prior-art-hans-haake-wide-white-flow.jpg" | prepend: site.baseurl }})
*Image by [Paula Cooper Gallery](https://www.paulacoopergallery.com)*

### SARndbox

From a technological standpoint the [Augmented Reality Sandbox](http://idav.ucdavis.edu/%7Eokreylos/ResDev/SARndbox/) created by Oliver Kreylos provided a many cues on how to setup my installation. It also outlined many of the necessary steps in order to align the 3D camera wit the projection.

<iframe width="560" height="315" src="https://www.youtube.com/embed/g6fSS3cynDo" frameborder="0" allowfullscreen></iframe>

### KREEK

This Project by [FLUUR](http://fluur.de/) was recommended to me by [Lorenz Potthast](http://www.lorenzpotthast.de/) after I showed him the documentation of my initial working prototype. Although it did not influence my project during its development it showed me that possible applications for the technology developed during my thesis go beyond its original intent of the intallation.

<iframe src="https://player.vimeo.com/video/174664186?color=ffffff" width="640" height="360" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>
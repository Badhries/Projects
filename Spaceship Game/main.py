#!/bin/python3
import turtle
import random
import math

# Setting up the screen for the game (Lines 21-24)
screen=turtle.Screen()
screen.setup(500, 500)
s_width = 500
s_height = 500

# Setting up images used in the game (Lines 27-40)
sky = {"turtle": turtle.Turtle(), "radius":35, "shape": "Night Sky.jpg"};
screen.bgpic("Night Sky.jpg")

harm = {"turtle": turtle.Turtle(), "radius":18, "shape": "rsz_harm.png"};
screen.addshape(harm["shape"])
harm["turtle"].shape(harm["shape"])

benefit = {"turtle": turtle.Turtle(), "radius":18, "shape": "rsz_1rsz_benefit.gif"};
screen.addshape(benefit["shape"])
benefit["turtle"].shape(benefit["shape"])

rocket = {"turtle": turtle.Turtle(), "radius":10, "shape": "rocketship.gif", "move_distance" : 5};
screen.addshape(rocket["shape"])
rocket["turtle"].shape(rocket["shape"])

#Moves rocket to the left of the screen (Lines 43-44)
rocket["turtle"].tracer(0)
rocket["turtle"].goto(int(-s_width/2.2) + int(rocket["radius"]/2.2), 0)



# Keypress for the Rocket(Lines 49-71)
def up():
  t = rocket["turtle"]
  if t.ycor() > s_height/2 - rocket["radius"]:
    return
  t.clear()
  current_y = t.ycor()
  t.sety(current_y + rocket["move_distance"])
  t.dot(rocket["radius"])
def down():
  t = rocket["turtle"]
  if t.ycor() < -s_height/2 + rocket["radius"]:
    return
  t.clear()
  current_y = t.ycor()
  t.sety(current_y - rocket["move_distance"])
  t.dot(rocket["radius"])

screen.onkey(up, "Up")
screen.onkey(down, "Down")
screen.onkey(up, "W")
screen.onkey(down, "S")

screen.listen()

# Turtle names for the three objects(Lines 74-76)
t = rocket["turtle"]
t1 = harm["turtle"]
t2 = benefit["turtle"]

# Harm/Benefit presence and movement control on screen(Lines 79-92)
t.tracer(0)
t1.tracer(0)
t2.tracer(0)
t1.hideturtle()
t1.setx(s_width/2)
t1.sety((random.randrange(int(-s_height/3), int(s_height/3))))
x = (random.randrange(int(-s_height/3), int(s_height/3)))
while abs(x - t1.ycor()) < 100:
  x = (random.randrange(int(-s_height/3), int(s_height/3)))
t2.sety(x)
t1.showturtle()
t2.hideturtle()
t2.setx(s_width/2)
t2.showturtle()

# Collision Detection requiremts and implementation for both the harm and benefit objects (Lines 95-111)
def are_colliding (rocket, benefit):
  collision_detected = False;
  dx = benefit["turtle"].xcor() - rocket["turtle"].xcor()
  dy = rocket["turtle"].ycor() - benefit["turtle"].ycor()
  distance = math.sqrt(dx * dx + dy * dy)
  if distance < rocket["radius"] + benefit["radius"]:
    collision_detected = True
  return collision_detected

def are_colliding (rocket, harm):
  collision_detected = False;
  dx =  harm["turtle"].xcor() - rocket["turtle"].xcor()
  dy = rocket["turtle"].ycor() - harm["turtle"].ycor()
  distance = math.sqrt(dx * dx + dy * dy)
  if distance < rocket["radius"] + harm["radius"]:
    collision_detected = True
  return collision_detected

# Score and Life Implementation (Lines 114-127)
Life = 3
score = 0
while (True):
  if are_colliding (rocket, benefit):
    t2.setx(s_width/2)
    t2.sety(random.randrange(int(-s_height/3), int(s_height/3)))
    score = score + 1
  if are_colliding (rocket, harm):
    t1.setx(s_width/2)
    t1.sety(random.randrange(int(-s_height/3), int(s_height/3)))
    Life = Life - 1
    
  t1.clear()
  t2.clear()
  
  # Determines how fast the benefit and harm object move(Lines 130 and 131)
  t1.setx(t1.xcor() - 2)
  t2.setx(t2.xcor() - 2)
  
  # Determines/randomizes the y coordinate of where the objects appear on the screen (Lines 134-148)
  if ((t1.xcor() - (harm["radius"])) <= -(s_width/2)):
    t1.hideturtle()
    t1.setx(s_width/2)
    t1.sety(random.randrange(int(-s_height/3), int(s_height/3)))
    t1.showturtle()
    
  if ((t2.xcor() - (benefit["radius"])) <= -(s_width/2)):
    t2.hideturtle()
    t2.setx(s_width/2)
    x = (random.randrange(int(-s_height/3), int(s_height/3)))
    while abs(x - t1.ycor()) < 100:
      x = (random.randrange(int(-s_height/2), int(s_height/2)))
    t2.sety(x)
      
    t2.showturtle()
  # Updating turtle and writing Life and Score on Screen then hiding turtle when the game is over (Lines 150-168)
  t1.update()
  t2.update()
  turtle.clear()
  turtle.color('green yellow')
  turtle.penup()
  turtle.goto(0, 225)
  turtle.hideturtle()
  turtle.write("Score: " + str(score), font=("Arial", 16))  
  turtle.goto(-100, 225)
  turtle.write("Life: " + str(Life), font=("Arial", 16))
  if Life == 0:
    turtle.goto(-170, 10)
    turtle.write("Game Over ", font=("Arial", 50))
    t.hideturtle()
    t1.hideturtle()
    t2.hideturtle()
    break
t1.update()
t2.update()

  





















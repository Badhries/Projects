#!/bin/python3
import urllib.request
import json
import pygal
day_counts_by_country = {}
list_of_dates = []
url = "https://raw.githubusercontent.com/pomber/covid19/master/docs/timeseries.json"
response = urllib.request.urlopen(url)
content = response.read()
data = json.loads(content)
for country in data:
  country_data = data[country]
  country_values = []
  for date_dict in country_data:
    str_date = date_dict["date"]
    split_date = str_date.split("-")
    month = int(split_date[1])
    if (date_dict["date"] >= ""):
      country_values.append(date_dict["confirmed"])
  day_counts_by_country[country] = country_values
list_of_tuples = []
for country in day_counts_by_country:
  country_day_counts = day_counts_by_country[country]
  most_recent_count = country_day_counts[-1]
  country_tuple = (country, most_recent_count)
  list_of_tuples.append(country_tuple)
sorted_list_of_tuples = sorted(list_of_tuples, key=lambda e:e[1], reverse = True) 
top_5 = sorted_list_of_tuples[0:5]
user_input = input("How many countries do you want to see the covid cases for?:")
line_chart = pygal.Line()
line_chart.title = 'Covid cases by date'
for tuple in range(int(user_input)):
  line_chart.add(sorted_list_of_tuples[int(tuple)][0], day_counts_by_country[sorted_list_of_tuples[int(tuple)][0]])
line_chart.render()
pie_chart = pygal.Pie()
pie_chart.title = 'Covid cases by country'
for tuple in sorted_list_of_tuples:
  country = tuple[0]
  pie_chart.add(country, tuple[1])
pie_chart.render()
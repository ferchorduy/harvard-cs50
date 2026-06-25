import csv
import requests

from datetime import datetime, timedelta


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if len(state) == 0:
            break
        if state in new_cases:
            states.append(state)
        # if len(state) == 0:
        #     break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    cases_today = {}
    rows = list(reader)
    last_date = rows[len(rows) - 1]['date']
    end_loop_date = get_to_this_date(last_date, -15)

    for row in range(len(rows) - 1, -1, -1):
        # print(f"{rows[row]['date']} {rows[row]['state']} {rows[row]['cases']}")
        state = rows[row]['state']
        cases = rows[row]['cases']
        date = rows[row]['date']

        if rows[row]['state'] not in cases_today:
            cases_today[state] = []
        if date == end_loop_date:
            break
        
        cases_today[state].append(cases)
            
    for state, total_cases in cases_today.items():
        yesterday = total_cases[1:]
        today = total_cases[:-1]
        new_cases[state] = list(map(lambda x, y: int(x) - int(y), today, yesterday))
    
    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        if state in new_cases:
            this_week_cases = new_cases[state][0:7]
            last_week_cases = new_cases[state][7:]
            this_week_average = round(sum(this_week_cases) / len(this_week_cases))
            last_week_average = round(sum(last_week_cases) / len(last_week_cases))
            try:
                percent_weekly_change = round(((this_week_average - last_week_average) / last_week_average) * 100)
            except ZeroDivisionError:
                print("No new cases last week")
                continue
            if percent_weekly_change == 0:
                print(f"{state} had a 7-day average in reported COVID cases of {this_week_average} and no change.")
            elif percent_weekly_change > 0:
                print(f"{state} had a 7-day average in reported COVID cases of {this_week_average} and an increase of {percent_weekly_change}%.")
            else:
                print(f"{state} had a 7-day average in reported COVID cases of {this_week_average} and a decrease of {-percent_weekly_change}%.")


def get_to_this_date(last_date: str, to_this_date: int):
    last_date_object = datetime.strptime(last_date, "%Y-%m-%d")
    past_date_object = last_date_object + timedelta(days=to_this_date)
    past_date = past_date_object.strftime("%Y-%m-%d")
    return past_date


main()

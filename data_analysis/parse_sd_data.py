from pathlib import Path
from datetime import datetime,  timedelta
from zoneinfo import ZoneInfo
from typing import Literal
import os


def parse_sd_data(file_name) -> None:
    file_path: Path = Path(__file__).with_name(file_name)
    with open(file_path, "r") as file_contents:
        data: list[str] = file_contents.readlines()
        today: datetime = datetime.now()
        start_time: datetime = datetime(year=today.year, month=int(file_name.split("-")[0]), day=int(file_name.split("-")[1].split(".")[0]),
                                        hour=16, minute=30, tzinfo=ZoneInfo("EST"))
        temp_logs: list[dict] = []
        over_forty_time: Literal[False] = False
        over_fifty_time: Literal[False] = False
        over_sixty_time: Literal[False] = False
        cleared_forty: Literal[False] = False
        cleared_fifty: Literal[False] = False
        cleared_sixty: Literal[False] = False

        time_counter: Literal[0] = 0
        prev: Literal[0] = 0
        for i in range(len(data)):
            time_counter += 1
            line: str = data[i]
            temp_data: dict = {}
            string_parts: list[str] = line.strip().split(",")
            temp: float = float(string_parts[1])

            # each line is 10 min interval
            time_stamp: datetime = start_time + \
                timedelta(minutes=time_counter * 10)

            if temp <= 43:
                cleared_forty = True
                if temp >= 41 and temp > prev and not over_forty_time:
                    over_forty_time = time_stamp

            if temp <= 53:
                cleared_fifty = True
                if temp >= 51 and temp > prev and not over_fifty_time:
                    over_fifty_time = time_stamp

            if temp <= 63:
                cleared_sixty = True
                if temp >= 60 and temp > prev and not over_sixty_time:
                    over_sixty_time = time_stamp

            prev = temp
            temp_data[time_stamp] = temp
            temp_logs.append(temp_data)

        print()
        runtime: datetime = list(
            temp_logs[len(temp_logs)-1].keys())[0] - start_time

        if over_forty_time:
            time_under_forty: datetime = over_forty_time - start_time
        else:
            if cleared_forty:
                time_under_forty = runtime
            else:
                time_under_forty = 0

        if over_fifty_time:
            time_under_fifty: datetime = over_fifty_time - start_time
        else:
            if cleared_fifty:
                time_under_fifty = runtime
            else:
                time_under_fifty = 0

        if over_sixty_time:
            time_under_sixty: datetime = over_sixty_time - start_time
        else:
            if cleared_sixty:
                time_under_sixty = runtime
            else:
                time_under_sixty = 0

        print('>>>>>>>>>>>>>>>>')
        print()
        print('RUNTIME >', runtime)
        print()
        print('TEST DATE >', start_time.date())
        print()
        print(f"RESULTS FOR {file_name}:")
        print()
        print('< 41°F:', time_under_forty, ","
              '< 51°F:', time_under_fifty, "< 60°F", time_under_sixty)
        print()


# txt_files: list[Path] = []
# arr = next(os.walk('.'))
# print(arr)
# print('os.getcwd()', os.getcwd())

# txt_files.extend()
parse_sd_data("1-9.TXT")
parse_sd_data("1-18.TXT")
parse_sd_data("1-19.TXT")
parse_sd_data("2-3-no_insulation.TXT")
parse_sd_data("2-3-insulation.TXT")
parse_sd_data("2-13-ABC_Supply_Double.TXT")
parse_sd_data("2-13-2x_AMZ_Supply_Single.TXT")
parse_sd_data("2-19-D-Wall.TXT")
parse_sd_data("2-19-D-Wall-2.TXT")
parse_sd_data("3-2-ABC-D-Wall-Brick.TXT")

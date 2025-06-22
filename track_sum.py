def add_times(time1: str, time2: str) -> str:
    minutes1, seconds1 = time1.split(':')
    seconds1, milliseconds1 = map(int, seconds1.split('.'))
    minutes1 = int(minutes1)

    minutes2, seconds2 = time2.split(':')
    seconds2, milliseconds2 = map(int, seconds2.split('.'))
    minutes2 = int(minutes2)

    total_minutes = minutes1 + minutes2
    total_seconds = seconds1 + seconds2
    total_milliseconds = milliseconds1 + milliseconds2

    if total_milliseconds >= 1000:
        total_seconds += total_milliseconds // 1000
        total_milliseconds %= 1000

    if total_seconds >= 60:
        total_minutes += total_seconds // 60
        total_seconds %= 60

    return f"{total_minutes:02}:{total_seconds:02}.{total_milliseconds:03}"


def is_valid_time_format(time_str: str) -> bool:
    try:
        minutes, seconds = time_str.split(':')
        seconds, milliseconds = seconds.split('.')
        return (len(minutes) >= 1 and len(seconds) == 2 and len(milliseconds) == 3 and
                minutes.isdigit() and seconds.isdigit() and milliseconds.isdigit())
    except ValueError:
        return False


def main() -> None:
    try:
        with open("input.txt", "r") as input_file:
            tracks: list[str] = [line.strip() for line in input_file.readlines()]
    except FileNotFoundError:
        print("Error opening the file.")
        return

    if not tracks:
        print("The input file is empty.")
        return

    total_time: str = "0:00.000"

    try:
        with open("output.txt", "w") as output_file:
            for track in tracks:
                if not is_valid_time_format(track):
                    print(f"Invalid track format: '{track}'. Expected format is mm:ss.sss.")
                    continue  # Skip invalid track

                total_time = add_times(total_time, track)
                print(total_time)  # Display on screen
                output_file.write(total_time + "\n")  # Write to the file
    except IOError:
        print("Error opening the output file.")
        return


if __name__ == "__main__":
    main()

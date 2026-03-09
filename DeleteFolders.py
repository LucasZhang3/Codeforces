import os
import shutil

# Root directory containing the numbered folders
ROOT_DIR = "."  # Change if needed


def is_numbered_folder(name):
    """
    Returns True if the folder name consists only of digits.
    """
    return name.isdigit()


def main():
    # Iterate through items in the root directory
    for item in os.listdir(ROOT_DIR):
        folder_path = os.path.join(ROOT_DIR, item)

        # Process only numbered directories
        if os.path.isdir(folder_path) and is_numbered_folder(item):

            # Move all files from the folder to ROOT_DIR
            for filename in os.listdir(folder_path):
                file_path = os.path.join(folder_path, filename)

                if os.path.isfile(file_path):
                    destination = os.path.join(ROOT_DIR, filename)

                    # If a file with the same name already exists, raise error
                    if os.path.exists(destination):
                        raise FileExistsError(
                            f"Cannot move {filename}: file already exists in root directory."
                        )

                    shutil.move(file_path, destination)

            # Remove the empty folder
            os.rmdir(folder_path)


if __name__ == "__main__":
    main()
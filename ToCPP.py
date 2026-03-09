import os

# Target directory
directory = r"C:\Users\Lucas\Downloads\CodeForces"

# Verify the directory exists
if not os.path.isdir(directory):
    raise FileNotFoundError(f"Directory not found: {directory}")

# Iterate through files in the directory
for filename in os.listdir(directory):
    if filename.lower().endswith(".txt"):
        old_path = os.path.join(directory, filename)
        
        # Create new filename with .cpp extension
        new_filename = os.path.splitext(filename)[0] + ".cpp"
        new_path = os.path.join(directory, new_filename)
        
        # Rename the file
        os.rename(old_path, new_path)
        print(f"Renamed: {filename} -> {new_filename}")

print("Done.")
import base64
import zlib

def compress_base64_encoded_file(file_path):
    # Read the binary content of the file
    with open(file_path, 'rb') as file:
        binary_data = file.read()
    
    # Encode the data to Base64
    base64_encoded_data = base64.b64encode(binary_data)
    
    # Compress the Base64 encoded data
    compressed_data = zlib.compress(base64_encoded_data)
    compressed_data = base64.b64encode(compressed_data).decode("utf-8")

    with open("compressed.txt", "w") as f:
        f.write(compressed_data)

compress_base64_encoded_file("chessbot4.so")
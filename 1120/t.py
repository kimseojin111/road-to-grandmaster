from PyPDF2 import PdfReader, PdfWriter

input_path = "서울과학고 합격자반 4주차 자료.pdf"
reader = PdfReader(input_path)
writer = PdfWriter()

# Pages 8-10 correspond to index 7,8,9 (0-based)
for i in range(3,10):
    writer.add_page(reader.pages[i])

output_path = "shit.pdf"
with open(output_path, "wb") as f:
    writer.write(f)

output_path

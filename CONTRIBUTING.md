**First of all** , let’s be clear: I am an Artist, not a professional Software Engineer. What you see in this repository is the result of sleepless nights, raw experimentation, and a 'brute force' approach to problem-solving. I don’t follow standard coding conventions; I follow the logic of making things work when everyone says they shouldn't.

[ USE AT YOUR OWN RISK ]
I take zero responsibility for any damage to your hardware, your sanity, or your printer. If you fry your EBB42 or blow up your MCU, that’s on you. This is experimental R&D territory.

[ A CALL TO THE EXPERTS ]
If you are a real developer and you're looking at my code thinking, 'What on earth was he doing here?'—please, do not hesitate to fix it. If you know how to optimize these drivers, clean up the syntax, or make the logic more efficient, I encourage you to fork this repo and show me the better way. I’m here to learn and to push the limits of my CB2 and my 4070 Ti. If I managed to make this work while being 'a disaster' at programming, imagine what we can do together.

[Hardware Integration: EBB42 Custom SPI Mapping]

To implement the MT6835 21-bit encoder on the BigTreeTech EBB42 (STM32G0B1), a custom hardware bypass was developed to overcome the lack of dedicated SPI pins.

Bypass Logic: The SPI signal is rerouted through the PT1000 pins (utilizing the non-MAX version of the EBB42). This allows for a direct SPI communication layer without interference from onboard temperature ICs.

Power Management: * The MT6835 is powered via the 5V pins natively exposed on the EBB42 header.

Since the encoder is 3.3V-5V tolerant, it integrates seamlessly with the logic levels of the STM32G0B1.

An additional LDO (Low-Dropout Regulator) is implemented to ensure a stable 3.3V rail, preventing noise-induced jitter in the 21-bit angle readings.

Firmware: The provided sensor_mt6835.c and angle.py are specifically tuned for this pin-mapping, ensuring full-duplex communication on the remapped bus.

______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

[SDXL Training Optimization (RTX 4070 Ti / 12GB VRAM]

Training SDXL on consumer-grade hardware requires surgical VRAM management. This setup utilizes OneTrainer with specific arguments to maintain stability and speed.

[ CORE LAUNCH ARGUMENTS ]

--PYTORCH_CUDA_ALLOC_CONF=expandable_segments:True: Essential to prevent memory fragmentation and OOM (Out Of Memory) errors on 12GB cards.

--lowvram / --medvram: (Specify which one you use) to balance tiling and speed.

--bf16: Utilizing BFLOAT16 precision to reduce memory footprint without losing the structural integrity of anatomical details.

[ CONFIG HIGHLIGHTS ]

Optimizer: AdamW 8-bit (to save ~2GB of VRAM compared to 32-bit).

Gradient Checkpointing: Enabled to trade a bit of speed for significant memory savings.

Effective Batch Size: Optimized via gradient accumulation to simulate higher stability on limited hardware.

# Low-Cost Air Filtration System for Desktop 3D Printer Emissions

**Status:** Final Draft - Project Complete

**Last Updated:** February 2026

---

## Abstract

Desktop fused deposition modeling (FDM) 3D printers emit ultrafine particles (UFPs) and volatile organic compounds (VOCs) during operation, presenting potential health concerns for users in enclosed spaces. This project presents the design, fabrication, and testing of a low-cost (<$100 USD) air filtration system for a desktop 3D printer enclosure where exterior venting is not feasible. The filtration system uses a commercial grow room carbon filter with a 4-inch inline fan. A custom 3D-printed mounting bracket with an over-center clamping mechanism enables tool-free installation and removal. Experimental validation was performed using Arduino-based metal-oxide (MOx) VOC sensors in a three-point wireless mesh configuration. Results demonstrate effective containment of emissions within the printer enclosure and minimal VOC propagation to the ambient environment.

**Keywords:** 3D printing safety, air filtration, VOC emissions, ultrafine particles, activated carbon, maker engineering

---

## 1. Introduction

### 1.1 Motivation and Problem Statement

Fused deposition modeling (FDM) has become increasingly accessible for home and small workshop use. However, the thermal decomposition of thermoplastic filaments during the printing process generates airborne contaminants that may pose health risks with chronic exposure. This project addresses the need for an affordable, effective filtration solution suitable for users in rental housing or other situations where permanent modifications (such as exterior venting) are not permitted.

### 1.2 Project Objectives

The primary objectives of this work were:

1. **Health Risk Assessment:** Characterize the types and quantities of emissions from desktop FDM printers based on published literature
2. **Filtration Design:** Develop a technically sound filtration methodology capable of removing both particulate and gaseous contaminants
3. **Mechanical Implementation:** Design and fabricate custom mounting hardware compatible with off-the-shelf components
4. **Experimental Validation:** Implement a measurement system to verify filtration effectiveness
5. **Cost Constraint:** Maintain total system cost below $100 USD to ensure accessibility

### 1.3 Design Constraints

- **Budget:** Maximum $100 USD for all components (limited use of peripheral hardware and equipment)
- **Space:** Must fit within/on existing printer enclosure (Ender 3 IKEA Lack Table Enclosure)
- **Infrastructure:** No exterior venting or permanent modifications allowed (rental apartment)
- **Operation:** Suitable for extended printing sessions with various filament types (PLA, ABS, PETG, Nylon)

**Note:** This documentation was prepared retrospectively after project completion. Some implementation details may be reconstructed from design files and experimental data.

**Historical Note:** At the time of this project, there were no open-source or cost-effective solutions that would actually perform adequately. There are now several solutions significantly better than this design available both commercially and as open source. The primary improvement over this design is recirculating filtration (closed loop) versus the open-loop approach used here, which provides better enclosure temperature control.

---

## 2. Literature Review

### 2.1 Emissions from Desktop 3D Printers

Desktop FDM printers generate two primary categories of airborne contaminants during operation: ultrafine particles (UFPs) and volatile organic compounds (VOCs). The emission rates and composition vary significantly by filament type and printing temperature.

#### 2.1.1 Ultrafine Particles (UFPs)

UFPs are particulate matter with aerodynamic diameter less than 100 nm. Published studies [1,2] characterize desktop 3D printer UFP emissions as follows:

**Particle Size Distribution:**
- Size range: 11.5 nm to 116 nm
- Classification: All emissions fall within the UFP category (<100 nm)

**Emission Rates by Filament Type:**
- PLA (Polylactic Acid): ~2.0 × 10¹⁰ particles/min
- ABS (Acrylonitrile Butadiene Styrene): ~1.9 × 10¹¹ particles/min (approximately 10× higher than PLA)

#### 2.1.2 Volatile Organic Compounds (VOCs)

VOC emissions result from thermal decomposition of polymer chains and residual monomers. Primary compounds identified include:

| Filament Type | Primary VOC | Emission Rate (μg/min) |
|---------------|-------------|------------------------|
| ABS, HIPS | Styrene | 10 – 110 |
| PLA | Lactide | 4 – 5 |
| Nylon-based | Caprolactam | 2 – 180 |

**Health Considerations:**
- Styrene: Classified as possibly carcinogenic to humans (IARC Group 2B); acute exposure causes mucous membrane irritation
- Lactide: Lower toxicity but prolonged exposure data limited
- Caprolactam: Eye and respiratory irritant

**Conclusion:** While there are no acute health issues from short-term VOC exposure, there are documented long-term effects with chronic exposure. Mitigation through filtration or ventilation is warranted for regular users.

For more information see this study: [Emissions of Ultrafine Particles and Volatile Organic Compounds from Commercially Available Desktop 3D Printers](https://pubs.acs.org/doi/abs/10.1021/acs.est.5b04983)

### 2.2 Existing Solutions

The maker community has developed several open-source filtration systems. The [Prusa Air Manager V2](https://www.prusaprinters.org/prints/16996-airmanagerv2-recirculating-air-filter-for-3d-print) represents a notable example of recirculating filtration systems. However, opportunities exist for optimization in filter selection, mounting hardware, and instrumentation.

---

## 3. Filtration Methodology

### 3.1 Filter Technology Evaluation

Three filter technologies were evaluated for suitability:
1. MERV (Minimum Efficiency Reporting Value) rated filters
2. HEPA (High-Efficiency Particulate Air) filters
3. Activated Carbon (Granulated and woven cloth forms)

#### 3.1.1 Particulate Filtration: MERV 16

**Selection Rationale:**

MERV 16 filters provide high-efficiency particulate removal across the UFP size range relevant to 3D printing [3]:

- UFP size range: 11.5 – 116 nm (0.0115 – 0.116 μm)
- MERV 16 specification: ≥75% efficiency for particles 0.3 – 1.0 μm, ≥95% for 1.0 – 3.0 μm
- Most Penetrating Particle Size (MPPS): ~0.1 – 0.3 μm

**Critical Analysis:**
While MERV 16 is specified for particles ≥0.3 μm, filtration efficiency typically increases for both larger AND smaller particles due to diffusion-dominated capture mechanisms below the MPPS. The 0.01 – 0.12 μm UFP range falls well below the MPPS, where Brownian motion enhances capture efficiency. Therefore, MERV 16 filtration is expected to provide near-complete UFP removal.

#### 3.1.2 VOC Adsorption: Granulated Activated Carbon (GAC)

HEPA and MERV filters remove particulates but do not capture gaseous contaminants. Activated carbon adsorption is the established technology for VOC removal in air purification applications.

**Form Factor Comparison:**

| Form Factor | Surface Area | Dwell Time | Mass | Assessment |
|-------------|--------------|------------|------|------------|
| Woven carbon cloth | Low | Very short | Minimal | Insufficient |
| Carbon foam sheets | Medium | Short | Low | Marginal |
| Granulated Activated Carbon (GAC) | High | Extended | High | Optimal |

**VOC Adsorption Capacity:**

Literature confirms that activated carbon effectively adsorbs the primary VOCs of concern [4,5]:
- Styrene (ABS): Confirmed adsorbed
- Lactide (PLA): Confirmed adsorbed
- Caprolactam (Nylon): Limited data; presumed effective based on molecular weight and polarity

### 3.2 First Design Attempt (Failed)

The first design attempt used an old computer fan with off-the-shelf MERV and GAC filter media. A rough prototype showed that the computer fan did not have enough static pressure to pass air effectively through the filtration medium. This approach was abandoned.

### 3.3 Final Solution: Commercial Grow Room Filter

While researching other affordable fan options, a commercial grow room carbon filter was identified as a viable solution. This pre-made filter paired with a standard 4-inch inline fan would meet the filtration objective.

**Selected Components:**

<p align="center">
  <a href="https://www.amazon.com/dp/B07VKJG4DQ">
    <img src="Images/carbon_filtration_inline_amazon.jpg" width="350" alt="Grow room carbon filter">
  </a>
  <a href="https://www.amazon.com/dp/B07ZL6FDYG">
    <img src="Images/4in-Inline-Fan.jpg" width="350" alt="4-inch inline fan">
  </a>
  <br>
  <em><a href="https://www.amazon.com/dp/B07VKJG4DQ">Carbon filter</a> (left) and <a href="https://www.amazon.com/dp/B07ZL6FDYG">4-inch inline fan</a> (right)</em>
</p>

**Final System Architecture:**
```
Enclosure Air → GAC Filter → Inline Fan → Exhaust
```

With this solution identified, the remaining task was to design a mount to attach the fan and filter to the enclosure.

---

## 4. Mechanical Design

### 4.1 Design Requirements

**Objective:** Design a 3D-printed mounting method that did not require modification of COTS parts and could be mounted to the exterior of an existing enclosure (Ender 3 IKEA Lack Table Enclosure).

**Functional Requirements:**
- Secure mounting for 4-inch inline fan
- No modification required to fan or filter
- Tool-free installation and removal
- Integration with existing printer enclosure
- Fully 3D-printed parts due to budget constraints

**Manufacturing Constraints:**
- Printable on consumer FDM printer (build volume, overhang limitations)
- Minimal support material usage
- Reasonable print time (<12 hours per component)
- Structural integrity for repeated use

### 4.2 Design Solution

The design settled on was a ring clamp around the fan comprising two half-cylinders with a print-in-place hinge and an over-center latching mechanism to provide the clamping force. The ring clamp would then twist-lock onto a mounting base plate screwed into the underside of the enclosure. Several holes would be drilled through the enclosure base to allow airflow.

Since the over-center mechanism was going to be the most difficult to design and would be relatively easy to print iterations (most likely faster and more reliable than performing advanced simulations), I decided to make the over-center mechanism a modular sub-assembly that mated to the ring clamp using a dovetail-style joint. This proved useful as there were 3 design iterations.

All parts were designed and modeled in Alibre Atom 3D using a spreadsheet-driven parametric approach for rapid iteration.

**Key Assemblies:**
- Fan ring clamp with print-in-place hinges
- Over-center toggle mechanism (3 iterations)
- Enclosure mounting plate

### 4.3 Over-Center Mechanism Design Iterations

The clamping mechanism underwent three design iterations:

| Version | Change | Outcome |
|---------|--------|---------|
| V1 | Initial geometry | Insufficient clamping force |
| V2 | Revised leverage ratio | Better force, but structurally weak |
| V3 | Reinforced linkages | Production version |

<p align="center">
  <img src="Images/Over_Center_Mech_V2_Iso_1.jpg" width="400" alt="Over-center clamping mechanism CAD model">
  <img src="Images/Over_Center_Mech_V2_Skeleton_Model.png" width="400" alt="Over-center mechanism skeleton model showing linkage geometry">
  <br>
  <em>Over-center clamping mechanism: CAD model (left) and skeleton model showing linkage geometry (right)</em>
</p>

### 4.4 Complete Assembly

<p align="center">
  <img src="Images/Exhaust_Holder_Asm_Iso_Adjusted.jpg" width="500" alt="Complete exhaust holder assembly CAD rendering">
  <br>
  <em>Complete exhaust holder assembly</em>
</p>

<p align="center">
  <img src="Images/Exhaust_Holder_Print_in_Place_Hinge.jpg" width="400" alt="Print-in-place hinge detail">
  <img src="Images/Exhaust_Holder_Top.jpg" width="400" alt="Top view of exhaust holder">
  <br>
  <em>Print-in-place hinge detail (left) and top view (right)</em>
</p>

### 4.5 Parametric Design Approach

A spreadsheet-driven parametric design methodology was employed to enable rapid design iteration and dimensional optimization. Key parameters controlled via spreadsheet include:
- Fan diameter and mounting hole spacing
- Clamp arm lengths and pivot locations
- Material thickness assumptions
- Clearance values

This approach allowed geometry updates without manual CAD rework, accelerating the design iteration cycle.

---

## 5. Manufacturing and Assembly

### 5.1 Print Settings

**Material:** PLA (adequate mechanical properties, dimensional stability, readily available)

**Print Parameters:**
- Layer height: 0.2 mm
- Infill: 20-25%
- Perimeters: 3-4 shells
- Supports: Minimal (design optimized for printability)

### 5.2 Print Files

All STL files are available in the [STL_and_GCode_Files/](STL_and_GCode_Files/) directory.

| Component | File | Print Time |
|-----------|------|------------|
| Fan Clamp | [Fan-Clamp.stl](STL_and_GCode_Files/Fan-Clamp.stl) | 9h 35min |
| Over-Center Mech V3 | [Over_Center_Mech_V3.stl](STL_and_GCode_Files/Over_Center_Mech_V3.stl) | 1h 40min |
| Mounting Plate | [Top_Female_Mount.stl](STL_and_GCode_Files/Top_Female_Mount.stl) | ~2h |

**Total assembly print time:** Approximately 12-15 hours
**Total material usage:** ~150-200g PLA (~$3-5 in material cost)

### 5.3 Assembly

All parts were printed and assembled.

A piece of closed-cell craft foam was used as a gasket between the enclosure and the mounting base to act as an air seal. No data on whether this was useful, but it seemed like a reasonable addition.

The mounting base was screwed to the underside of the enclosure using standard washer-head wood screws.

<p align="center">
  <img src="Images/Fan_Clamp_2.jpg" width="500" alt="Installed filter ring clamp on fan with over-center clamp mechanism">
  <br>
  <em>Installed filter ring clamp on fan with over-center clamp mechanism</em>
</p>

<p align="center">
  <img src="Images/Fully_Installed.jpg" width="500" alt="Installed system on enclosure">
  <br>
  <em>Installed system on enclosure</em>
</p>

---

## 6. VOC Measurement System

### 6.1 Sensor Technology Selection

Conventional VOC monitoring equipment (photo-ionization detectors, gas chromatography) costs $3,000 – $50,000+, far exceeding the project budget. An alternative approach using low-cost metal-oxide (MOx) semiconductor gas sensors was identified.

#### 6.1.1 Metal-Oxide (MOx) Sensor Principles

MOx sensors detect VOCs through conductivity changes in a heated metal oxide layer when gas molecules adsorb to the surface. Modern MOx sensors (SGP30, SGP40) implement sophisticated algorithms to output a normalized "VOC Index" that correlates with total VOC concentration.

**Selected Sensors:**
- **Primary VOC sensing:** Sensirion SGP40 MOx sensor (~$15-20 each)
- **Environmental compensation:** Sensirion SHT31 temperature/humidity sensor (~$15 each)

MOx sensors require temperature and humidity compensation for accurate readings, necessitating the integrated sensor suite.

**Limitations:**
- Measure *total* VOC concentration (not individual species)
- Require warm-up and calibration period
- Sensitive to cross-interference from other gases (acceptable for relative measurements)

### 6.2 Three-Point Measurement Configuration

To characterize filtration effectiveness, three sensor nodes were deployed:

| Node | Location | Purpose |
|------|----------|---------|
| Gateway | Connected to PC via serial | Data logging and control measurement |
| Node 1 | Inside printer enclosure | Measure emission source concentration |
| Node 2 | Filter outlet / room baseline | Measure filtration effectiveness |

**Expected Results:**
- Baseline: Low, stable VOC index
- Enclosure: Elevated VOC index during printing
- Outlet: VOC index approaching baseline (ideally within 5-10%)

### 6.3 Hardware Design

**Hardware per sensor node:**
- Arduino Nano 328p (16MHz)
- Sensirion SGP40 MOx VOC sensor (I²C interface, address 0x59)
- Sensirion SHT31 temperature/humidity sensor (I²C interface, address 0x44)
- NRF24L01 radio module for wireless mesh communication

For detailed wiring information, see the [Wiring Diagram](Images/wiring_diagram.md).

<p align="center">
  <img src="Images/VOC_Sensor_Protoboard_Front.jpg" width="400" alt="VOC sensor protoboard front">
  <img src="Images/VOC_Sensor_Protoboard_back.jpg" width="400" alt="VOC sensor protoboard back">
  <br>
  <em>Arduino-based VOC sensor protoboard: front (left) and back (right)</em>
</p>

### 6.4 Software Architecture

The sensor system uses the [MySensors](https://www.mysensors.org/) library to create a self-healing wireless mesh network:

| Node | Role | Sketch | Description |
|------|------|--------|-------------|
| Gateway | Serial bridge | [GatewaySerial_with_voc_sensor/](Arduino_VOC_Sensor_Code/GatewaySerial_with_voc_sensor/) | Receives data from nodes, outputs to serial/PC |
| Node 1 | Enclosure sensor | [NODEl_with_voc_sensor/](Arduino_VOC_Sensor_Code/NODEl_with_voc_sensor/) | Inside printer enclosure |
| Node 2 | Baseline sensor | [NODE2_with_voc_sensor/](Arduino_VOC_Sensor_Code/NODE2_with_voc_sensor/) | Filter outlet / room baseline |

**Software Implementation:**
- **Libraries:** MySensors (wireless mesh), Adafruit_SGP40, Adafruit_SHT31
- **Sampling interval:** 1 second (1000ms update cycle)
- **Data transmitted per node:**
  - Temperature (converted to Fahrenheit)
  - Relative humidity (%)
  - Raw VOC sensor value (unitless)
  - Computed VOC Index (0-500 scale)

The sensor nodes transmit temperature, humidity, raw VOC values, and computed VOC index to the gateway, which logs data to MongoDB via the Home Assistant MySensors plugin over USB serial. Data was displayed via Home Assistant and Grafana dashboards.

**Standalone logging sketch:**
A simpler [sgp40_voc_logging.ino](Arduino_VOC_Sensor_Code/sgp40_voc_logging.ino) is also included for single-sensor serial logging without wireless capability.

Source code available in [Arduino_VOC_Sensor_Code/](Arduino_VOC_Sensor_Code/) directory.

---

## 7. Results

### 7.1 Filtration Performance

**What worked:**
- VOC levels in surrounding room remained at baseline during extended prints
- No detectable odor outside enclosure during printing
- System operated reliably
- Budget achieved: ~$85-95 total

### 7.2 Data Availability

**Note:** Unfortunately, the experimental data was not saved, and the sensor protoboards have since been damaged (the cats used them as toys). As such, working data and graphs cannot be provided.

### 7.3 Areas for Improvement

Based on testing and extended use, the following improvements are recommended:

1. **Higher clamping force and better air sealing for the ring clamp**
2. **Stronger over-center mechanism linkages** - experienced stress fractures after repeated cycling
3. **In-depth simulation and analysis** - as a learning opportunity, perform FEA on the clamping force and structural strength of the over-center mechanism
4. **Different filtration method** - explore methods that allow for air recirculation, which would provide better thermal control
5. **Thermal management** - if the enclosure is well sealed, the plastic melts too high up in the hot end and prevents extrusion. Leaving the doors open resolves this while still keeping VOC emissions low.

---

## 8. Cost Analysis

### 8.1 Total System Cost

**Target:** <$100 USD
**Actual:** ~$85-95 USD (estimated; exact receipts not available)

**Cost Distribution (approximate):**
- Sensors and electronics: $50-60
- Fan: $10-15
- Filter: $15-20
- 3D printed components: $5
- Miscellaneous: $5-10

**Conclusion:** Project successfully met the budget constraint while achieving functional filtration performance.

---

## 9. Conclusions

This project successfully demonstrated that effective air filtration for desktop 3D printer emissions can be achieved within a constrained budget suitable for hobbyist users. The key accomplishments include:

1. **Technical Validation:** Literature review confirmed health concerns from 3D printer emissions and established technical basis for filtration approach
2. **Effective Design:** Commercial carbon filter successfully removed VOC contaminants
3. **Custom Hardware:** 3D-printed mounting bracket enabled integration with off-the-shelf components
4. **Empirical Verification:** Arduino-based VOC sensing confirmed filtration effectiveness
5. **Budget Achievement:** Total system cost remained under $100 USD target

---

## 10. References

1. Stephens, B., et al. (2013). "Ultrafine particle emissions from desktop 3D printers." *Atmospheric Environment*, 79, 334-339. https://www.sciencedirect.com/science/article/pii/S1352231013005086

2. Azimi, P., et al. (2016). "Emissions of Ultrafine Particles and Volatile Organic Compounds from Commercially Available Desktop Three-Dimensional Printers with Multiple Filaments." *Environmental Science & Technology*, 50(3), 1260-1268. https://pubs.acs.org/doi/abs/10.1021/acs.est.5b04983

3. U.S. Environmental Protection Agency. "What is a MERV Rating?" https://www.epa.gov/indoor-air-quality-iaq/what-merv-rating-1

4. Wikipedia contributors. "Activated carbon - Environmental applications." *Wikipedia*. https://en.wikipedia.org/wiki/Activated_carbon#Environmental

5. Sentry Air Systems. "Activated Carbon Adsorption." https://www.sentryair.com/activated-carbon-adsorption.htm

6. Leidinger, M., et al. (2019). "Correlating MOx sensor data to identify gaseous pollutant species." *Atmospheric Measurement Techniques*, 12, 1441-1460. https://amt.copernicus.org/articles/12/1441/2019/amt-12-1441-2019.pdf

### Additional Resources

- Adafruit SGP40 Air Quality Sensor: https://learn.adafruit.com/adafruit-sgp40/overview
- Adafruit SHT31 Temperature & Humidity Sensor: https://www.adafruit.com/product/2857
- SGP40 Arduino Library: https://github.com/adafruit/Adafruit_SGP40
- MySensors Library: https://www.mysensors.org/

### Community Prior Art

- Prusa Air Manager V2: https://www.prusaprinters.org/prints/16996-airmanagerv2-recirculating-air-filter-for-3d-print

---

## Appendices

### Appendix A: Design Files

All CAD files were created in Alibre Atom 3D and are available in this repository:

**Assembly:**
- [Exhaust Holder.AD_ASM](Exhaust%20Holder.AD_ASM)

**Component Files:**
- [Fan-Clamp.AD_PRT](Fan-Clamp.AD_PRT)
- [Fan_Clamp_LeftHand.AD_PRT](Fan_Clamp_LeftHand.AD_PRT)
- [Fan.AD_PRT](Fan.AD_PRT)
- [Over_Center_Mech_V2.AD_PRT](Over_Center_Mech_V2.AD_PRT)
- [Over_Center_Mechanism.AD_PRT](Over_Center_Mechanism.AD_PRT)
- [Top_Female_Mount.AD_PRT](Top_Female_Mount.AD_PRT)

### Appendix B: 3D Printable Files

STL files ready for slicing (located in [STL_and_GCode_Files/](STL_and_GCode_Files/) directory):

- [Exhaust_Holder_clamp.stl](STL_and_GCode_Files/Exhaust_Holder_clamp.stl)
- [Fan-Clamp.stl](STL_and_GCode_Files/Fan-Clamp.stl)
- [Fan_Clamp_LeftHand.stl](STL_and_GCode_Files/Fan_Clamp_LeftHand.stl)
- [Over_Center_Mechanism.stl](STL_and_GCode_Files/Over_Center_Mechanism.stl)
- [Over_Center_Mechanism_v2.stl](STL_and_GCode_Files/Over_Center_Mechanism_v2.stl)
- [Over_Center_Mech_V3.stl](STL_and_GCode_Files/Over_Center_Mech_V3.stl)
- [Top_Female_Mount.stl](STL_and_GCode_Files/Top_Female_Mount.stl)

### Appendix C: Arduino Source Code

All Arduino sketches are available in the [Arduino_VOC_Sensor_Code/](Arduino_VOC_Sensor_Code/) directory:

**Standalone Serial Logging:**
- [sgp40_voc_logging.ino](Arduino_VOC_Sensor_Code/sgp40_voc_logging.ino) - Simple serial output for single sensor testing

**MySensors Wireless Mesh Network:**
- [GatewaySerial_with_voc_sensor/](Arduino_VOC_Sensor_Code/GatewaySerial_with_voc_sensor/) - Gateway node (serial bridge to PC)
- [NODEl_with_voc_sensor/](Arduino_VOC_Sensor_Code/NODEl_with_voc_sensor/) - Sensor Node 1 (enclosure)
- [NODE2_with_voc_sensor/](Arduino_VOC_Sensor_Code/NODE2_with_voc_sensor/) - Sensor Node 2 (baseline)

**Required Libraries:**
- MySensors (wireless mesh networking)
- Adafruit_SGP40 (VOC sensor)
- Adafruit_SHT31 (temperature/humidity sensor)

### Appendix D: Wiring Diagram

For detailed sensor node wiring, see [Images/wiring_diagram.md](Images/wiring_diagram.md).

**Pin Connections Summary:**

| Bus | Arduino Pin | Device | Pin |
|-----|-------------|--------|-----|
| SPI | D13 | NRF24L01 | SCK |
| SPI | D12 | NRF24L01 | MISO |
| SPI | D11 | NRF24L01 | MOSI |
| SPI | D10 | NRF24L01 | CSN |
| SPI | D9 | NRF24L01 | CE |
| I2C | A4 | SGP40/SHT31 | SDA |
| I2C | A5 | SGP40/SHT31 | SCL |
| Power | 3.3V | All modules | VCC/VIN |
| Power | GND | All modules | GND |

---

## Skills Demonstrated

| Category | Skills |
|----------|--------|
| **Mechanical Design** | Alibre Atom 3D, parametric CAD, DFM for FDM printing, mechanism design |
| **Research** | Literature review, technical analysis, experimental design |
| **Prototyping** | 3D printing, iterative design, hands-on fabrication |
| **Electronics** | Arduino, I2C sensors, wireless mesh networking (NRF24/MySensors), data acquisition |
| **Software** | Embedded C/C++, sensor integration, serial communication protocols |
| **Documentation** | Technical writing, project documentation |

---

*Last Updated: February 2026*
